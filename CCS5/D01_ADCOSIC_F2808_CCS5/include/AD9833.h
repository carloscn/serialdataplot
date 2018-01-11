/*
 * AD9833.h
 *
 *  Created on: 2015年9月4日
 *      Author: Davis
 */

#ifndef AD9833_H_
#define AD9833_H_



/////////////////////////////////////////////////////////////////////
//AD9833时钟线
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define			SCLK					GpioDataRegs.GPBDAT.bit.GPIOB0//J45
#define			FSYNC					GpioDataRegs.GPBDAT.bit.GPIOB1
#define			SDATA					GpioDataRegs.GPBDAT.bit.GPIOB2


//AD9833
//#define			MHz						1000000
//#define			KHz						1000
#define			Sin_Wave				0x2000
#define			Tri_Wave				0x2002
#define			Squ_Wave			0x2020

extern void API_AD9833_VOID_GenerateWaveforms( long Freq , Uint16 Phase , Uint16 Wave );

/////////////////////////////////////////////////////////////////////
#endif /* AD9833_H_ */
