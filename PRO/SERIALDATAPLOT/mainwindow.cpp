// Qt for windows   Project.
/****************************************************************************/
/*                                                                          */
/*  @file       : *_main    .cpp                  	                        */
/*  @Copyright  : Powered by MULTIBEANS ORG rights reserved.                */
/*  @Revision   : Ver 1.0.                                                  */
/*  @Data       : 2018.01.04 Realse.                                        */
/*  @Belong     : PROJECT.                                                  */
/*  @Git        : https://github.com/lifimlt/serialdataplot.git             */
/*  **code : (UTF-8) in Windows 10      . Qt 5.8.0 for Windows platform.    */
/****************************************************************************/
/*  @Attention:                                                             */
/*  ---------------------------------------------------------------------   */
/*  |    Data    |  Behavior |     Offer      |          Content         |  */
/*  | 2018.01.04 |   create  |Carlos Lopez(M) | ceate the document.      |  */
/*  ---------------------------------------------------------------------   */
/*  Email: carlos@mltbns.top                                  MULTIBEANS.   */
/****************************************************************************/
/*--------------------------------------------------------------------------*/
/*    Copyright (C) 2018  POWERED BY MULTIBEANS                             */
/*                                                                          */
/*    This program is free software: you can redistribute it and/or modify  */


/*    it under the terms of the GNU General Public License as published by  */
/*    the Free Software Foundation, either version 3 of the License, or     */
/*    (at your option) any later version.                                   */

/*    This program is distributed in the hope that it will be useful,       */

/*    but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/*    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/*    GNU General Public License for more details.                          */

/*    You should have received a copy of the GNU General Public License     */
/*    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

/*--------------------------------------------------------------------------*/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qmath.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple Wave Display System V1.0");
    // 初始化文本信息
    ui->textBrowser->append(tr("--------------------------------------------------------------- "));
    ui->textBrowser->append(tr("SYSTEM: Welcome to use the Simaple Wave Display system!"));
    ui->textBrowser->append(tr("SYSTEM: The window will remind the message of system and print the orignal signals!"));
    ui->textBrowser->append(tr("SYSTEM: notice : Inorder to avoid the software crash, please wait 3 seconds for the system initing."));
    ui->textBrowser->append(tr("---------------------------------------------------------------- "));

    // 初始化串口
    serialPort = new QSerialPort;
    serialPort->setBaudRate(QSerialPort::Baud9600);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(on_serial_readBuffer_ready()));
    // 初始化按钮
    ui->button_stopDevice->setEnabled(false);
    ui->button_startDevice->setEnabled(true);
    refreshTheDeviceList();
    allowTheDeviceRefresh = true;
    currentConnectCom = tr("NULL");


    // Init QCustomPlot Class
    xcount = 0;
    xrange = 500;
    ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    ui->plot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    ui->plot->addGraph();
    ui->plot->xAxis->setLabel("points(n)");
    ui->plot->yAxis->setLabel("ADC Signal Magtitude");
    ui->plot->xAxis->setRange(0, xrange);
    ui->plot->yAxis->setRange(0, 500);
#if false
    //ui->plot->graph(0)->setBrush(QBrush(QColor(240, 255, 200)));
    ui->plot->graph(0)->setPen(QPen(Qt::red));
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    for(int i; i < 500; i ++ ) {
        ui->plot->graph(0)->addData(i,6*sin(2*i*0.1) + 10 +  0.1*(qrand()%10));
    }

    ui->plot->replot();

#endif
    bool_packet_done = false;
    qint32_adc_packet_count = 0;
    error_mid_string.clear();
    error_left_string.clear();
    error_right_string.clear();
    double_adc_max_data = 500;
    double_adc_min_data = 0;
#if 0
    QString temp1 = ".3,888.9,@@@###,178.5,185.5,456.8,658.3,85.6,@@@###,416";
    int head_index_start = temp1.indexOf("###");
    int head_index_tail = temp1.indexOf("@@@");
    QString current_string = temp1.mid( head_index_start + 3 ,  head_index_tail - head_index_start - 3 );
    qDebug() << "head:" << head_index_start ;
    qDebug() << "tail"  << head_index_tail;
    qDebug() << current_string;
    QList<QString> list_adc_datas_string = current_string.split(',');

    qDebug() <<"1:" << list_adc_datas_string.at(0);
    qDebug() <<"2:" << list_adc_datas_string.at(1);
    qDebug() <<"3:" << list_adc_datas_string.at(2);
    qDebug() <<"4:" << list_adc_datas_string.at(3);
    qDebug() <<"5:" << list_adc_datas_string.at(4);
#endif
}

MainWindow::~MainWindow()
{
    delete ui;
}
// ###178.5,185.5,456.8,658.3,85.6@@@
// The serial recieved data slot function.
void MainWindow::on_serial_readBuffer_ready()
{

    double adc_packet_datas[5];
    QString serial_datas_string;
    QList<QString> list_adc_datas_string;

    int head_index_start;
    int data_packet_length;
    int head_index_tail;

    serialReadArray.append( serialPort->readAll() );
    serial_datas_string = error_mid_string + QString( serialReadArray );
    qDebug() << "rec:" << serial_datas_string;

    // S1: 提取一个完整的数据 ### ........   @@@
    // 判断数据是否包含###和@@@和数据两边偏移
    // .3,888.9,@@@###,178.5,185.5,456.8,658.3,85.6,@@@###,416
    head_index_start = serial_datas_string.indexOf("###");
    head_index_tail = serial_datas_string.indexOf("@@@");
    data_packet_length = serial_datas_string.length();

    if( serial_datas_string.contains("###") && serial_datas_string.contains("@@@") ) {

         // 如果###字符不是文字头，则前边有数据
        if( head_index_start != 0 ) {
            // 保存左边的字符
            error_left_string = serial_datas_string.left( head_index_start );

        }
        // 如果@@@末尾字符不是文字尾，则和右边有数据
        if( head_index_tail != data_packet_length ) {
            // 保存右边的字符
            error_right_string = serial_datas_string.right( head_index_tail );
        }
        if( (!serial_datas_string.contains("@@@") && !serial_datas_string.contains("###") ) &&
            ( serial_datas_string.indexOf("###") > serial_datas_string.indexOf("@@@")  )  ) {
             return;
        }

    }
    // 数据单边左偏移，数据包一定在上一次的接收中
    // .3,888.9,@@@###,178.5,185.5,456.8,658.3,85.6,@@@###,416
    if( serial_datas_string.contains("@@@") && !serial_datas_string.contains("###") ) {

        // 和上一次接收的数据组合成一个完整的数据包
        serial_datas_string = error_right_string + serial_datas_string;
        if( head_index_tail != data_packet_length ) {
            // 保存右边的字符
            error_right_string = serial_datas_string.right( head_index_tail );
        }
        if( (!serial_datas_string.contains("@@@") && !serial_datas_string.contains("###") ) &&
            ( serial_datas_string.indexOf("###") > serial_datas_string.indexOf("@@@")  )  ) {
             return;
        }
    }

    // 数据单边右偏移, 数据包一定在下一次接收中
    // ###,178.5,185.5,456.8,658.3
    if( serial_datas_string.contains("###") && !serial_datas_string.contains("@@@") ) {
        serial_datas_string = serial_datas_string + error_left_string;
        // 如果###字符不是文字头，则前边有数据
        if( head_index_start != 0 ) {
            // 保存左边的字符
            error_left_string = serial_datas_string.left( head_index_start );
        }
       if( (!serial_datas_string.contains("@@@") && !serial_datas_string.contains("###") ) &&
           ( serial_datas_string.indexOf("###") > serial_datas_string.indexOf("@@@")  )  ) {
            return;
       }

    }
    if( !serial_datas_string.contains("@@@") && !serial_datas_string.contains("###") ) {
        error_mid_string = serial_datas_string;
        return;
    }

    // 提取###和@@@中间的数
    QString current_string = serial_datas_string.mid( head_index_start + 3,  head_index_tail - head_index_start - 3);

    list_adc_datas_string = current_string.split(',');
    adc_packet_datas[0] = list_adc_datas_string.at(1).toDouble();
    adc_packet_datas[1] = list_adc_datas_string.at(2).toDouble();
    adc_packet_datas[2] = list_adc_datas_string.at(3).toDouble();
    adc_packet_datas[3] = list_adc_datas_string.at(4).toDouble();
    adc_packet_datas[4] = list_adc_datas_string.at(5).toDouble();

    ui->plot->graph(0)->addData(qint32_adc_packet_count + 0, adc_packet_datas[0]);
    ui->plot->graph(0)->addData(qint32_adc_packet_count + 1, adc_packet_datas[1]);
    ui->plot->graph(0)->addData(qint32_adc_packet_count + 2, adc_packet_datas[2]);
    ui->plot->graph(0)->addData(qint32_adc_packet_count + 3, adc_packet_datas[3]);
    ui->plot->graph(0)->addData(qint32_adc_packet_count + 4, adc_packet_datas[4]);
    ui->plot->replot();
    qint32_adc_packet_count += 5 ;
    bool_packet_done = false;

    // 横坐标自动适配
    if( qint32_adc_packet_count % 500 == 0 ) {
        xrange += 500;
        ui->plot->xAxis->setRange(xrange - 500, xrange);
        ui->plot->replot();
    }
    // 纵坐标自动适配
    if( minValue( adc_packet_datas ) <= double_adc_min_data ) {
        double_adc_min_data = minValue( adc_packet_datas );
        ui->plot->yAxis->setRange(double_adc_min_data - 50, double_adc_max_data + 50 );
        ui->plot->replot();
    }
    if( maxValue( adc_packet_datas ) >= double_adc_max_data ) {
        double_adc_max_data = maxValue( adc_packet_datas );
        ui->plot->yAxis->setRange(double_adc_min_data - 50 , double_adc_max_data + 50 );
        ui->plot->replot();
    }
    qDebug() << "maxValue :" << maxValue( adc_packet_datas );
    qDebug() << "minValue :" << minValue( adc_packet_datas );
    // 清除数据
    serialReadArray.clear();
}

double MainWindow::maxValue( double *data )
{
    double max = 0;
    max = *(data);
    for( int i = 0; i < 5; i++ ) {
        if( *(data + i) > max ) {
            max = *(data + i);
        }
    }
    return max;
}
double MainWindow::minValue( double *data )
{
    double min = 0;
    min = *(data);
    for( int i = 0; i < 5; i++ ) {
        if( *(data + i) < min ) {
            min = *(data + i);
        }
    }
    return min;
}

void MainWindow::refreshTheDeviceList()
{
    QString portName;
    QString uartName;
    QSerialPortInfo info;
    ui->deviceBox->clear();

    ui->textBrowser->append(tr("SYSTEM: Refreshing the device list."));
    //foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    foreach (info, QSerialPortInfo::availablePorts())
    {
        serialPort->setPort(info);
        portName = info.portName();
        uartName = info.description();
        ui->deviceBox->addItem(portName +" (" +uartName+") "  );
        ui->textBrowser->append(tr("SYSTEM: Scan the uart device: ")+uartName + "("+portName+")"+tr(" has been added to the available list! "));
        qDebug()<<"get: " << portName;

    }

}

void MainWindow::checkTheDeviceRemove()
{
    QString portName;
    QSerialPortInfo info;

    bool checked = false;
    foreach (info, QSerialPortInfo::availablePorts())
    {
        portName = info.portName();
        if( portName.compare(currentConnectCom) == 0 ) {
            checked = true;
        }
    }
    if( checked == false ) {
        QMessageBox::information(this,"Warning", "UART: "+ currentConnectCom +" has been removed! \n");
        ui->button_scanDevice->setEnabled(true);
        ui->button_startDevice->setEnabled(true);
        ui->button_stopDevice->setEnabled(false);
        ui->deviceBox->setEnabled(true);
        serialPort->close();
        allowTheDeviceRefresh = true;
        refreshTheDeviceList();
    }

}
// USB
bool MainWindow::nativeEvent(const QByteArray & eventType, void * message, long *result)
{

    MSG* msg = reinterpret_cast<MSG*>(message);
    int msgType = msg->message;
    if(msgType==WM_DEVICECHANGE)
    {
        //qDebug() << "Event DEVICECHANGE Happend" << endl;
        PDEV_BROADCAST_HDR lpdb = (PDEV_BROADCAST_HDR)msg->lParam;
        switch (msg->wParam) {
        case DBT_DEVICEARRIVAL:
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags ==0)
                {

                    //QString USBDisk = QString(this->FirstDriveFromMask(lpdbv ->dbcv_unitmask));
                    //qDebug() << "USB_Arrived and The USBDisk is: "<<USBDisk ;
                    //ui->textBrowser->append("USB_Arrived and The USBDisk is " + USBDisk);

                }
            }
            if(lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;

                QString strname = QString::fromWCharArray(pDevInf->dbcc_name,pDevInf->dbcc_size);
                ui->textBrowser->append("SYSTEM: Checked a USB-DEVICE is having a request that connects to the system.");

                if( allowTheDeviceRefresh == true ) {
                    refreshTheDeviceList();
                }
                //qDebug() << "Device inserted:" + strname;
                //ui->textBrowser->append("Device inserted:" + strname);
            }
            break;
        case DBT_DEVICEREMOVECOMPLETE:
            qDebug() << "remove the device" <<endl;
            if(lpdb->dbch_devicetype == DBT_DEVTYP_VOLUME)
            {
                PDEV_BROADCAST_VOLUME lpdbv = (PDEV_BROADCAST_VOLUME)lpdb;
                if(lpdbv->dbcv_flags == 0)
                {

                }
            }
            if(lpdb->dbch_devicetype = DBT_DEVTYP_DEVICEINTERFACE)
            {
                PDEV_BROADCAST_DEVICEINTERFACE pDevInf  = (PDEV_BROADCAST_DEVICEINTERFACE)lpdb;
                qDebug()<< "removed the device name:" << pDevInf->dbcc_name;
                qDebug()<< "removed the device guid :" << pDevInf->dbcc_classguid;
                qDebug()<< "removed the device size : " << pDevInf->dbcc_size;
                ui->textBrowser->append("SYSTEM:check a USB_Device has been removed!");
                checkTheDeviceRemove();
                if( allowTheDeviceRefresh == true ) {
                    refreshTheDeviceList();
                }
                //QString strname = QString::fromWCharArray(pDevInf->dbcc_name,pDevInf->dbcc_size);

                //ui->textBrowser->append("removed the device: " + strname);
            }
            break;
        }
    }
    return false;
}

char MainWindow::FirstDriveFromMask (ULONG unitmask)
{
    char i;

    for (i = 0; i < 26; ++i)
    {
        if (unitmask & 0x1)
            break;
        unitmask = unitmask >> 1;
    }
    return (i + 'A');
}

void MainWindow::findUartDevice()
{
    QString portName;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        QSerialPort serial;
        serial.setPort(info);
        if (serial.open(QIODevice::ReadWrite))
        {
            portName = info.portName();
            ui->deviceBox->addItem(portName);
            ui->textBrowser->append(tr("SYSTEM: Scan the uart device: ")+info.portName()+tr(" has been added to the available list! "));
            qDebug()<<portName;
            //serialPort->setPortName(info.portName());
            //serial.close();
        }
    }

}





void MainWindow::on_button_scanDevice_clicked()
{
    refreshTheDeviceList();
}

void MainWindow::on_button_startDevice_clicked()
{
    QSerialPort serial;
    if( ui->deviceBox->currentIndex() == -1 ) {
        QMessageBox::warning(this,"Warring","Please click the Scan button firstly to check available devices. Then connect after selecting one device in list. ");
        return;
    }
    QString portName=ui->deviceBox->currentText();
    currentConnectCom = portName.mid(0,4);
    ui->textBrowser->append(tr("SYSTEM: Serial port ")+portName+tr(" ,system is connecting with it....."));
    serialPort->setPortName(currentConnectCom);
    //serial.close();

    if (!serialPort->open(QIODevice::ReadWrite))
    {
        QMessageBox::warning(this,"Warring","Open serial port fail!");
        ui->textBrowser->append(tr("SYSTEM: Serial port failed to open, please check whether the serial port is occupied by other software, or check the serial connection is normal!"));
        ui->deviceBox->setEnabled(true);
    }
    else
    {

        ui->textBrowser->append(tr("SYSTEM: The system has been connected with ")+portName+" " );
        ui->button_stopDevice->setEnabled(true);
        ui->button_startDevice->setEnabled(false);
        QMessageBox::information(this,"Information", "UART: "+ portName+" has been connected! \n"+"Wait GPS sensor signals.");
        ui->deviceBox->setEnabled(false);
        ui->button_scanDevice->setEnabled(false);
        allowTheDeviceRefresh = false;

    }

    qDebug() << "The serial has been openned!! \n";
}

void MainWindow::on_button_stopDevice_clicked()
{
    serialPort->close();

    QMessageBox::information(this,"Success", "Serial port has been closed!");
    ui->textBrowser->append(tr("SYSTEM: The serial port has been closed! You can't use the system now. "));
    ui->button_stopDevice->setEnabled(false);
    ui->button_startDevice->setEnabled(true);
    ui->deviceBox->setEnabled(true);
    ui->button_scanDevice->setEnabled(true);
    allowTheDeviceRefresh = true;
}

void MainWindow::on_pushButton_clearBrower_clicked()
{
    ui->textBrowser->clear();
}
