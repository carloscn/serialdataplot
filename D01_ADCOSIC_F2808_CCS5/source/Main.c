// TMS320F2808	 Project.
/****************************************************************************/
/*									 										*/
/*	@file 		: *_Main.c									 				*/
/*	@Copyright	: DavisBeans.(c) 2015 MULTIBEANS_ORG All rights reserved.	*/
/*  @Revision	: Ver 1.0.													*/
/*  @Data		: 2016.04.27 Realse.										*/
/*  @Belong		: PROJECT.							 						*/
/*																		    */
/*	**code : (GBK/GB2312) in win_10_x64. CCS v6.1 platform.			    	*/
/****************************************************************************/
/*	@Attention:																*/
/* 	---------------------------------------------------------------------	*/
/*	|    Data    |	Behavior |     Offer	 |    		Content			|	*/
/*  | 2018.11.20 |   creat   | DavisBeans(M) |   creat the document.	|	*/
/*  ---------------------------------------------------------------------	*/
/* 															  MULTIBEANS.	*/
/****************************************************************************/

//###########################################################################
// $TI Release: F281x C/C++ Header Files and Peripheral Examples V130 $
// $Release Date: May  8, 2015 $
// $Copyright: Copyright (C) 2009-2015 Texas Instruments Incorporated -
//             http://www.ti.com/ ALL RIGHTS RESERVED $
//###########################################################################
#include "DSP280x_Device.h"
#include "DSP280x_Examples.h"
#include "IQmathLib.h"
#include "AD9833.h"
#include "string.h"
#include "stdlib.h"

/**
 * @brief  Reports the name of the source file and the source line number
 *         where the assert_param error has occurred.
 * @param  file: pointer to the source file name
 * @param  line: assert_param error line source number
 * @retval None
 */


#define POST_SHIFT   0  // Shift results after the entire sample table is full
#define INLINE_SHIFT 1  // Shift results as the data is taken from the results regsiter
#define NO_SHIFT     0  // Do not shift the results

// ADC start parameters
#define ADC_MODCLK 0x4   // HSPCLK = SYSCLKOUT/2*ADC_MODCLK2 = 100/(2*4)      = 12.5 MHz
//    for 60 MHz devices:    HSPCLK =  60/(2*4)      =  7.5 MHz
#define ADC_CKPS   0x0   // ADC module clock = HSPCLK/1      = 12.5MHz/(1)    = 12.5 MHz
//    for 60 MHz devices: ADC module clk = 7.5MHz/(1)=  7.5 MHz
#define ADC_SHCLK  0x1   // S/H width in ADC module periods                   = 2 ADC cycle
#define AVG        1000  // Average sample limit
#define ZOFFSET    0x00  // Average Zero offset
#define BUF_SIZE   1000  // Sample buffer size
#define DELAY_US_ADC	400000

////////////////////////////////////////////////////////////////////////
#define STRINGDATA_SIZE  50      //
////////////////////////////////////////////////////////////////////////
#define			RXA_MAX_COUNT			10

Uint16 rxaInterruptCount = 0;
Uint16 AdcInterruptCount = 0;
char rxaBuffer[RXA_MAX_COUNT]={0};
Uint16 SampleTable[BUF_SIZE];
char charSampleData[];

interrupt void SCIA_RX_ISR( void );
interrupt void ADC_Interrupt( void );

void ADC_Init();
void EVA_init();
void SCIA_INIT();
void SendDatasByScia();
void intTochar();
void GPIO_INIT();
Uint16 SendOnceDataPacket( Uint16 *datas_buffer );
void ClearBuffer( unsigned char *buffer, Uint16 length );
void FloatToASCII( float data , unsigned char *buffer);

Uint16 array_index = 0;
float adc = 0;
unsigned char str[10]="";
Uint16 adc_i = 0;
unsigned char stringDataSend[ STRINGDATA_SIZE ]=  "###,";//设置一个字符串，用于存储拼接数据
int breakpoint=0;

void main( void )
{

	unsigned char adc_datas_buffer[20];
	Uint16 i;

	ClearBuffer( adc_datas_buffer, sizeof( adc_datas_buffer ) );
	InitSysCtrl();

	EALLOW;
	SysCtrlRegs.HISPCP.all = ADC_MODCLK; // HSPCLK = SYSCLKOUT/ADC_MODCLK
	EDIS;
	//	GPIO_INIT();
	InitSciaGpio();
	InitCpuTimers();
	InitPieCtrl();
	IER = 0x0000;
	IFR = 0x0000;
	InitPieVectTable();


	InitAdc();         // For this example, init the ADC

	ADC_Init();
	DELAY_US(1000);
	SCIA_INIT();
	DELAY_US(1000);

	// Interrupts that are used in this example are re-mapped to
	// ISR functions found within this file.
	PieCtrlRegs.PIEIER9.bit.INTx1 = 1;
	PieCtrlRegs.PIEIER9.bit.INTx3 = 1;

	IER |= M_INT9;
	IER |= M_INT1;
	EINT;
	ERTM;

	// Clear SampleTable
	for (adc_i=0; adc_i<BUF_SIZE; adc_i++)
	{
		SampleTable[adc_i] = 0;
	}
	// Start SEQ1
	AdcRegs.ADCTRL2.all = 0x2000;

	//AD9833初始化
	//第一个参数是频率，单位为Hz || 第二个参数是相位，默认为0 || 第三个参数是波形
	//	API_AD9833_VOID_GenerateWaveforms( 50, 0 , Sin_Wave);
	//ADC初始化



	while(1) {

		DELAY_US( DELAY_US_ADC );					//延迟单位为us，   延迟1ms  采样频率为1KHz

		while (AdcRegs.ADCST.bit.INT_SEQ1== 0){}
		AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;


		SampleTable[ adc_i ]= ( ( AdcRegs.ADCRESULT0 ) >> 4 );
		if ( adc_i >= 4 ) {
			SendOnceDataPacket( SampleTable );
			adc_i = 0;
		}
		adc_i ++;

	}
}

void ClearBuffer( unsigned char *buffer, Uint16 length )
{
	Uint16 i;
	for( i = 0; i < length; i++ ) {
		*(buffer + i) = '\0';
	}
}

Uint16 SendOnceDataPacket( Uint16 *datas_buffer )
{
	Uint16 i;
	Uint16 data;
	unsigned char data_char[15];


	ClearBuffer( stringDataSend, sizeof( stringDataSend ) );

	// Write Comunicate Head to sendBuffer.
	stringDataSend[0] = '#';
	stringDataSend[1] = '#';
	stringDataSend[2] = '#';
	stringDataSend[3] = ',';
	// Process five datas, convert them to char.
	for( i = 0; i < 5; i++ ) {
		data = *(datas_buffer + i);
		strcat( stringDataSend, itoa(data) );
	}
	strcat( stringDataSend, ",@@@\0" );
	SendDatasByScia( stringDataSend );

	ClearBuffer( stringDataSend, sizeof( stringDataSend ) );
}

void SendDatasByScia( unsigned char *_ch )
{
	Uint16 i = 0;
	//	Uint16 j = 0;
	//	j = strlen(_ch);
	//	for(i = 0; i <=j; i++) {
	while(*(_ch+i) != '\0'){
		while(SciaRegs.SCICTL2.bit.TXRDY==0);//状态检测模式
		while(SciaRegs.SCICTL2.bit.TXEMPTY==0);//状态检测，等待发送标识为空
		SciaRegs.SCITXBUF = *(_ch+i)&0xFF;
		while(SciaRegs.SCICTL2.bit.TXEMPTY==0);//确保最后一个数据发送出去
		i++;
	}
	//	i = 0;
}



interrupt void ADC_Interrupt( void )
{

	adc = ((float)AdcRegs.ADCRESULT0) * 3.0 /65520.0;
	while( AdcInterruptCount ++ == 1024 )
		AdcInterruptCount = 0;

	PieCtrlRegs.PIEACK.all = 0x0001;//响应PIE同组中断
	AdcRegs.ADCTRL2.bit.RST_SEQ1 = 1;//复位序列发生器SEQ1
	AdcRegs.ADCST.bit.INT_SEQ1_CLR = 1;//清除AD中断标志位

	EINT;											//使能全局中断
}


//ADC初始化
void ADC_Init()
{
	AdcRegs.ADCTRL1.bit.ACQ_PS = ADC_SHCLK;  // Sequential mode: Sample rate   = 1/[(2+ACQ_PS)*ADC clock in ns]
	//                     = 1/(3*80ns) =4.17MHz (for 100 MHz devices or
	//                     = 1/(3*133ns) = 2.51 MHz (for 60 MHz devices)
	// If Simultaneous mode enabled: Sample rate = 1/[(3+ACQ_PS)*ADC clock in ns]
	AdcRegs.ADCTRL3.bit.ADCCLKPS = ADC_CKPS;
	AdcRegs.ADCTRL1.bit.SEQ_CASC = 1;        // 1  Cascaded mode
	AdcRegs.ADCCHSELSEQ1.bit.CONV00 = 0x0;
	AdcRegs.ADCTRL1.bit.CONT_RUN = 1;       // Setup continuous run

	AdcRegs.ADCTRL1.bit.SEQ_OVRD = 1;       // Enable Sequencer override feature
	AdcRegs.ADCCHSELSEQ1.all = 0x0;         // Initialize all ADC channel selects to A0
	AdcRegs.ADCCHSELSEQ2.all = 0x0;
	AdcRegs.ADCCHSELSEQ3.all = 0x0;
	AdcRegs.ADCCHSELSEQ4.all = 0x0;
	AdcRegs.ADCMAXCONV.bit.MAX_CONV1 = 0x0;  // convert and store in 8 results registers

}

void FloatToASCII( float data , unsigned char *buffer) {

	Uint16 i,j = 1;
	unsigned char AsciiBuff[14];
	if( data < 0 ) {
		data = -data;
		AsciiBuff[0] = '-';
	}else{
		AsciiBuff[0] = '+';
	}
	AsciiBuff[1] 	= 	( long ) ( data/10000000 ) % 10 + 0x30;
	AsciiBuff[2] 	= 	( long ) ( data/1000000 ) % 10 + 0x30;
	AsciiBuff[3] 	= 	( long ) ( data/100000 ) % 10 + 0x30;
	AsciiBuff[4] 	= 	( Uint16 ) ( data/10000 ) %10 + 0x30;
	AsciiBuff[5]	= 	( Uint16 ) ( data/1000 ) %10 + 0x30;
	AsciiBuff[6] 	= 	( Uint16 ) ( data/100 ) %10 + 0x30;
	AsciiBuff[7] 	= 	( Uint16 ) ( data/10 ) %10 + 0x30;
	AsciiBuff[8] 	= 	( Uint16 ) ( (long)( data ) % 10 ) + 0x30;
	AsciiBuff[9] 	= 	46;
	AsciiBuff[10] 	= 	( ( long ) ( data * 10 ) % 10 ) + 0x30 ;
	AsciiBuff[11] 	= 	( ( long ) ( data * 100 ) % 10 ) + 0x30 ;
	AsciiBuff[12] 	= 	(long)'\0';

	if( AsciiBuff[1] == 48 && AsciiBuff[2] == 48 && AsciiBuff[3] == 48 && AsciiBuff[4]  ==  48
			&& AsciiBuff[5]  ==  48 && AsciiBuff[6]  ==  48 && AsciiBuff[7]  ==  48     ) {
		for( i = 1; i < 8; i++ )
			AsciiBuff[i] = 32;
	}
	if( AsciiBuff[6] == 48 && AsciiBuff[1] == 48 && AsciiBuff[2] == 48 && AsciiBuff[3]  ==  48
			&& AsciiBuff[4]  ==  48 && AsciiBuff[5]  ==  48  ) {
		for( i = 1; i < 7; i++ )
			AsciiBuff[i] = 32;
	}
	if( AsciiBuff[5] == 48 && AsciiBuff[1] == 48 && AsciiBuff[2] == 48 && AsciiBuff[3]  ==  48
			&& AsciiBuff[4]  ==  48 ) {
		for( i = 1; i < 6; i++ )
			AsciiBuff[i] = 32;
	}
	if( AsciiBuff[4] == 48 && AsciiBuff[1] == 48 && AsciiBuff[2] == 48 && AsciiBuff[3]  ==  48  ) {
		for( i = 1; i < 5; i++ )
			AsciiBuff[i] = 32;
	}
	if( AsciiBuff[3] == 48 && AsciiBuff[1] == 48 && AsciiBuff[2] == 48 ) {
		AsciiBuff[3] = 32;
		AsciiBuff[1] = 32;
		AsciiBuff[2] = 32;
	}
	if( AsciiBuff[2] == 48 && AsciiBuff[1] == 48 ) {
		AsciiBuff[2] = 32;
		AsciiBuff[1] = 32;
	}
	if(AsciiBuff[1] == 48) {
		AsciiBuff[1] = 32;
	}
	for( i = 0; i < 13; i++ ) {
		if( AsciiBuff[i] != 32 ){
			*(buffer + j) = AsciiBuff[i];
			*(buffer + j + 1) = '\0';
			j++;
		}
	}
}


interrupt void SCIA_RX_ISR( void )
{

	rxaBuffer[ rxaInterruptCount ] = SciaRegs.SCIRXBUF.all;

	rxaInterruptCount ++;

	if( rxaInterruptCount == RXA_MAX_COUNT  ) {
		rxaInterruptCount = 0;						// over the range.
	}

	PieCtrlRegs.PIEACK.all = 0x0101;
	EINT;
}




//=============================================================
// FUNCTION:    SCIA_INIT
// DESCRIPTION: Configures SCIA
//
// PARAMETERS:  SciaRegs
// RETURN:      N/A
//=============================================================
void SCIA_INIT()
{
	SciaRegs.SCICCR.bit.STOPBITS = 0;//1位结束位
	SciaRegs.SCICCR.bit.PARITYENA = 0;//禁止奇偶校验功能
	SciaRegs.SCICCR.bit.LOOPBKENA = 0;//禁止回送测试功能
	SciaRegs.SCICCR.bit.ADDRIDLE_MODE = 0;//空闲线模式协议
	SciaRegs.SCICCR.bit.SCICHAR = 7;//8位数据位

	SciaRegs.SCICTL1.bit.TXENA = 1;//SCIA发送使能
	SciaRegs.SCICTL1.bit.RXENA = 1;//SCIA接收使能

	SciaRegs.SCIHBAUD    =0x0001;  // 9600 baud @LSPCLK = 20MHz.
	SciaRegs.SCILBAUD    =0x0044;

	//	SciaRegs.SCIHBAUD    =0x0000;  // 115200 baud @LSPCLK = 20MHz.
	//	SciaRegs.SCILBAUD    =0x00AE;

	//	SciaRegs.SCIHBAUD = 0;
	//	SciaRegs.SCILBAUD = 0x28;
	//波特率为115200bps 0x28
	//波特率为19200bps 0xF3

	SciaRegs.SCICTL2.bit.RXBKINTENA = 1;//SCIA接收中断使能
	SciaRegs.SCICTL2.bit.TXINTENA = 1;	 //SCIA发送中断使能

	SciaRegs.SCICTL1.bit.SWRESET = 1;//复位信号，重启SCI
}


//=============================================================
// FUNCTION:    GPIO_INIT
// DESCRIPTION: Configures all GPIO
//
// PARAMETERS:  GpioCtrlRegs
// RETURN:      N/A
//=============================================================
void GPIO_INIT(  )
{
	EALLOW;

	////////////////////////////////////////////////////////////////////
	/////////////////////     GPIO CONFIGURE  //////////////////////////
	////////////////////////////////////////////////////////////////////
	/* Enable internal pull-up for the selected pins */
	// Pull-ups can be enabled or disabled disabled by the user.
	// This will enable the pullups for the specified pins.

	GpioCtrlRegs.GPAPUD.bit.GPIO28 = 1;    // Enable pull-up for GPIO28 (SCIRXDA)
	GpioCtrlRegs.GPAPUD.bit.GPIO29 = 1;   // Enable pull-up for GPIO29 (SCITXDA)
	//	REG->GPFMUX.bit.SCIRXDA_GPIOF5 = 1;//设置为功能引脚，启用SCI功能，下同
	//	REG->GPFMUX.bit.SCITXDA_GPIOF4 = 1;
	//    REG->GPGMUX.bit.SCIRXDB_GPIOG5 = 1;
	//    REG->GPGMUX.bit.SCITXDB_GPIOG4 = 1;


	EDIS;

}

void intTochar( int _data, char *_str)
{
	int i;
	int scaleData=0;
	int intData = _data;
	int intDatatmp = _data;
	int tmpData=0;
	char str[10]=" ";
	char strlong[10]="0";
	//计算数据长度
	for (i = 0; i < 10; ++i) {
		if ( intDatatmp != 0 ) {
			intDatatmp = intDatatmp / 10;
		} else {
			scaleData = i;break;
		}
	}
	//开始将int型转换为char型数据
	for (i = 0; i < scaleData; ++i) {
		tmpData = intData % 10;
		intData = intData / 10;
		switch (tmpData) {
		case 0:str[ i ] = '0';break;
		case 1:str[ i ] = '1';break;
		case 2:str[ i ] = '2';break;
		case 3:str[ i ] = '3';break;
		case 4:str[ i ] = '4';break;
		case 5:str[ i ] = '5';break;
		case 6:str[ i ] = '6';break;
		case 7:str[ i ] = '7';break;
		case 8:str[ i ] = '8';break;
		case 9:str[ i ] = '9';break;
		default:	break;
		}
	}
	if(scaleData == 0)
	{
		_str[0] = '1';
	}else{
		strcat(strlong,str);
		for (i = 0; i < scaleData; ++i) {
			_str[i] = strlong[ scaleData - i ];
		}
	}
}

char* itoa( int val, char* dst, int radix )
{
	char *_pdst = dst;
	if (!val)//允许val等于0
	{
		*_pdst = '0';
		*++_pdst = '\0';
		return dst;
	}
	if(val <0)
	{
		*_pdst++ = '-';
		val = -val;
	}
	char *_first = _pdst;
	char _cov;
	unsigned int _rem;
	while(val > 0)
	{
		_rem = (unsigned int)(val % radix);
		val /= radix;//每次计算一位 ，从低到高
		if  (_rem > 9)//16进制
			*_pdst++ = (char)(_rem - 10 + 'a');
		else
			*_pdst++ = (char)(_rem + '0');
	}
	*_pdst-- = '\0';
	do{ //由于数据是地位到高位储存的，需要转换位置
		_cov = *_pdst;
		*_pdst = *_first;
		*_first = _cov;
		_pdst--;
		_first++;
	}while(_first < _pdst);
	return dst;
}


