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

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Simple Wave Display System V1.0");
    // 初始化文本信息
    ui->textBrowser->append(tr("--------------------------------------------------------------- "));
    ui->textBrowser->append(tr("SYSTEM: Welcome to use the Simaple Wave Display system!"));
    ui->textBrowser->append(tr("SYSTEM: The window will remind the message of system and print the orignal GPS signals!"));
    ui->textBrowser->append(tr("SYSTEM: notice : Inorder to avoid the software crash, please wait 3 seconds for the system initing."));
    ui->textBrowser->append(tr("---------------------------------------------------------------- "));

    // 初始化串口
    serialPort = new QSerialPort;
    serialPort->setBaudRate(QSerialPort::Baud115200);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(QSerialPort::NoParity);
    serialPort->setStopBits(QSerialPort::OneStop);
    serialPort->setFlowControl(QSerialPort::NoFlowControl);
    connect(serialPort,SIGNAL(readyRead()),this,SLOT(RxData()));
    // 初始化按钮
    ui->button_stopDevice->setEnabled(false);
    ui->button_startDevice->setEnabled(true);
    refreshTheDeviceList();
    allowTheDeviceRefresh = true;
    currentConnectCom = tr("NULL");


    //  初始化变量
    xcount = 0;
    xrange = 50;
    ui->plot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom)); // period as decimal separator and comma as thousand separator
    ui->plot->legend->setVisible(true);
    QFont legendFont = font();  // start out with MainWindow's font..
    legendFont.setPointSize(9); // and make a bit smaller for legend
    ui->plot->legend->setFont(legendFont);
    ui->plot->legend->setBrush(QBrush(QColor(255,255,255,230)));
    // by default, the legend is in the inset layout of the main axis rect. So this is how we access it to change legend placement:
    ui->plot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignBottom|Qt::AlignRight);
    // 生成数据，画出的是抛物线
    ui->plot->addGraph();
    // 为坐标轴添加标签
    ui->plot->xAxis->setLabel("x");
    ui->plot->yAxis->setLabel("y");
    // 设置坐标轴的范围，以看到所有数据
    ui->plot->xAxis->setRange(0, xrange);
    ui-> plot->yAxis->setRange(0, 50);

    ui->plot->graph(0)->addData(10,10);
    ui->plot->graph(0)->addData(10,11);
    ui->plot->graph(0)->addData(10,12);
    ui->plot->replot();
}

MainWindow::~MainWindow()
{
    delete ui;
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
