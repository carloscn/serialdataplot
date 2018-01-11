#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QByteArray>
#include <Windows.h>
#include <dbt.h>
#include "qcustomplot.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QCustomPlot *plot;
    long xcount;
    long xrange;
public :
    double maxValue( double *data );
    double minValue( double *data );
private slots:
    void on_button_scanDevice_clicked();
    void on_button_startDevice_clicked();
    void on_button_stopDevice_clicked();
    void on_pushButton_clearBrower_clicked();
    void on_serial_readBuffer_ready();

private:
    Ui::MainWindow *ui;
    void findUartDevice( void );
    char FirstDriveFromMask (unsigned long unitmask);
    void refreshTheDeviceList();
    void checkTheDeviceRemove();
    bool nativeEvent(const QByteArray & eventType, void * message, long *result);

private:
    QSerialPort *serialPort;
    QByteArray serialReadArray;
    bool serialRead;
    bool allowTheDeviceRefresh;
    QString currentConnectCom;
    bool bool_packet_done;
    qint32 qint32_adc_packet_count;

    QString error_left_string;
    QString error_right_string;
    QString error_mid_string;
    double double_adc_max_data;
    double double_adc_min_data;
    qint64 qint64_adc_recevie_count;
};

#endif // MAINWINDOW_H
