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

private slots:
    void on_button_scanDevice_clicked();
    void on_button_startDevice_clicked();
    void on_button_stopDevice_clicked();
    void on_pushButton_clearBrower_clicked();

private:
    Ui::MainWindow *ui;
    void findUartDevice( void );
    char FirstDriveFromMask (unsigned long unitmask);
    void refreshTheDeviceList();
    void checkTheDeviceRemove();
    bool nativeEvent(const QByteArray & eventType, void * message, long *result);

    QSerialPort *serialPort;
    QByteArray rxArray;
    bool serialRead;
    bool allowTheDeviceRefresh;
    QString currentConnectCom;
};

#endif // MAINWINDOW_H
