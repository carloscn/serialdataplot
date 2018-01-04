/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_7;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_6;
    QComboBox *deviceBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *button_scanDevice;
    QPushButton *button_startDevice;
    QPushButton *button_stopDevice;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser;
    QPushButton *pushButton_clearBrower;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_4;
    QCustomPlot *plot;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1560, 690);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_7 = new QLabel(centralWidget);
        label_7->setObjectName(QStringLiteral("label_7"));

        verticalLayout_4->addWidget(label_7);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setStyleSheet(QStringLiteral(""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setMinimumSize(QSize(120, 0));
        label_6->setMaximumSize(QSize(120, 16777215));

        horizontalLayout_2->addWidget(label_6);

        deviceBox = new QComboBox(groupBox);
        deviceBox->setObjectName(QStringLiteral("deviceBox"));
        deviceBox->setMinimumSize(QSize(400, 0));
        deviceBox->setMaximumSize(QSize(400, 16777215));

        horizontalLayout_2->addWidget(deviceBox);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        button_scanDevice = new QPushButton(groupBox);
        button_scanDevice->setObjectName(QStringLiteral("button_scanDevice"));
        button_scanDevice->setStyleSheet(QLatin1String("background-color: rgb(170, 0, 255);\n"
"\n"
""));

        horizontalLayout_3->addWidget(button_scanDevice);

        button_startDevice = new QPushButton(groupBox);
        button_startDevice->setObjectName(QStringLiteral("button_startDevice"));
        button_startDevice->setStyleSheet(QStringLiteral("background-color: rgb(255, 0, 127);"));

        horizontalLayout_3->addWidget(button_startDevice);

        button_stopDevice = new QPushButton(groupBox);
        button_stopDevice->setObjectName(QStringLiteral("button_stopDevice"));
        button_stopDevice->setStyleSheet(QStringLiteral("background-color: rgb(255, 255, 0);"));

        horizontalLayout_3->addWidget(button_stopDevice);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_4->addWidget(groupBox);

        groupBox_2 = new QGroupBox(centralWidget);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setStyleSheet(QStringLiteral(""));
        verticalLayout_2 = new QVBoxLayout(groupBox_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        textBrowser = new QTextBrowser(groupBox_2);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setMinimumSize(QSize(0, 0));
        textBrowser->setStyleSheet(QStringLiteral("font: 7pt \"Consolas\";"));

        verticalLayout_2->addWidget(textBrowser);

        pushButton_clearBrower = new QPushButton(groupBox_2);
        pushButton_clearBrower->setObjectName(QStringLiteral("pushButton_clearBrower"));
        pushButton_clearBrower->setStyleSheet(QStringLiteral("background-color: rgb(170, 255, 0);"));

        verticalLayout_2->addWidget(pushButton_clearBrower);


        verticalLayout_4->addWidget(groupBox_2);


        horizontalLayout->addLayout(verticalLayout_4);

        groupBox_3 = new QGroupBox(centralWidget);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        horizontalLayout_4 = new QHBoxLayout(groupBox_3);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        plot = new QCustomPlot(groupBox_3);
        plot->setObjectName(QStringLiteral("plot"));
        plot->setMinimumSize(QSize(1080, 600));
        plot->setMaximumSize(QSize(1080, 600));

        horizontalLayout_4->addWidget(plot);


        horizontalLayout->addWidget(groupBox_3);


        verticalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1560, 26));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:22pt; font-weight:600;\">Simple Wave Display System</span></p></body></html>", Q_NULLPTR));
        groupBox->setTitle(QApplication::translate("MainWindow", "Control Panel", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindow", "Devices List:", Q_NULLPTR));
        button_scanDevice->setText(QApplication::translate("MainWindow", "Scan", Q_NULLPTR));
        button_startDevice->setText(QApplication::translate("MainWindow", "Connect", Q_NULLPTR));
        button_stopDevice->setText(QApplication::translate("MainWindow", "Disconnect", Q_NULLPTR));
        groupBox_2->setTitle(QApplication::translate("MainWindow", "Information", Q_NULLPTR));
        pushButton_clearBrower->setText(QApplication::translate("MainWindow", "Clear", Q_NULLPTR));
        groupBox_3->setTitle(QApplication::translate("MainWindow", "Plot Area", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
