/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QComboBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_2;
    QLabel *label_6;
    QPushButton *pushButton_softTrig;
    QPushButton *pushButton;
    QSpinBox *spinBox_GainValue;
    QComboBox *cbAutoTrig;
    QSlider *horizontalSlider_FpgaFreq;
    QSlider *horizontalSlider_GainValue;
    QCheckBox *checkBox_AutoGain;
    QLabel *label_5;
    QLineEdit *lineEdit_Width;
    QLineEdit *lineEdit_Height;
    QLabel *label_3;
    QSpinBox *spinBox_FpgaFreq;
    QLabel *label_7;
    QCheckBox *checkBox_AutoExpo;
    QLabel *label;
    QLabel *label_4;
    QSlider *horizontalSlider_ExpoValue;
    QSpinBox *spinBox_ExpoValue;
    QComboBox *imgchannel;
    QLabel *label_8;
    QLabel *imgdisplayer;
    QPlainTextEdit *IMUtext;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(725, 690);
        MainWindow->setAcceptDrops(false);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        layoutWidget = new QWidget(centralWidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(3, 2, 437, 202));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton_2, 0, 3, 1, 3);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 3, 2, 1, 1);

        pushButton_softTrig = new QPushButton(layoutWidget);
        pushButton_softTrig->setObjectName(QString::fromUtf8("pushButton_softTrig"));

        gridLayout->addWidget(pushButton_softTrig, 5, 2, 1, 1);

        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        sizePolicy.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy);

        gridLayout->addWidget(pushButton, 0, 0, 1, 3);

        spinBox_GainValue = new QSpinBox(layoutWidget);
        spinBox_GainValue->setObjectName(QString::fromUtf8("spinBox_GainValue"));
        spinBox_GainValue->setMinimum(16);
        spinBox_GainValue->setMaximum(63);

        gridLayout->addWidget(spinBox_GainValue, 4, 5, 1, 1);

        cbAutoTrig = new QComboBox(layoutWidget);
        cbAutoTrig->setObjectName(QString::fromUtf8("cbAutoTrig"));

        gridLayout->addWidget(cbAutoTrig, 2, 2, 1, 1);

        horizontalSlider_FpgaFreq = new QSlider(layoutWidget);
        horizontalSlider_FpgaFreq->setObjectName(QString::fromUtf8("horizontalSlider_FpgaFreq"));
        horizontalSlider_FpgaFreq->setMaximum(60);
        horizontalSlider_FpgaFreq->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_FpgaFreq, 2, 4, 1, 1);

        horizontalSlider_GainValue = new QSlider(layoutWidget);
        horizontalSlider_GainValue->setObjectName(QString::fromUtf8("horizontalSlider_GainValue"));
        horizontalSlider_GainValue->setMinimum(16);
        horizontalSlider_GainValue->setMaximum(63);
        horizontalSlider_GainValue->setPageStep(10);
        horizontalSlider_GainValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_GainValue, 4, 3, 1, 2);

        checkBox_AutoGain = new QCheckBox(layoutWidget);
        checkBox_AutoGain->setObjectName(QString::fromUtf8("checkBox_AutoGain"));
        checkBox_AutoGain->setChecked(true);

        gridLayout->addWidget(checkBox_AutoGain, 4, 0, 1, 2);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 2, 1, 1);

        lineEdit_Width = new QLineEdit(layoutWidget);
        lineEdit_Width->setObjectName(QString::fromUtf8("lineEdit_Width"));

        gridLayout->addWidget(lineEdit_Width, 1, 1, 1, 2);

        lineEdit_Height = new QLineEdit(layoutWidget);
        lineEdit_Height->setObjectName(QString::fromUtf8("lineEdit_Height"));

        gridLayout->addWidget(lineEdit_Height, 1, 4, 1, 2);

        label_3 = new QLabel(layoutWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 2);

        spinBox_FpgaFreq = new QSpinBox(layoutWidget);
        spinBox_FpgaFreq->setObjectName(QString::fromUtf8("spinBox_FpgaFreq"));

        gridLayout->addWidget(spinBox_FpgaFreq, 2, 5, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 2, 3, 1, 1);

        checkBox_AutoExpo = new QCheckBox(layoutWidget);
        checkBox_AutoExpo->setObjectName(QString::fromUtf8("checkBox_AutoExpo"));
        checkBox_AutoExpo->setChecked(true);

        gridLayout->addWidget(checkBox_AutoExpo, 3, 0, 1, 2);

        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 1, 3, 1, 1);

        horizontalSlider_ExpoValue = new QSlider(layoutWidget);
        horizontalSlider_ExpoValue->setObjectName(QString::fromUtf8("horizontalSlider_ExpoValue"));
        horizontalSlider_ExpoValue->setMaximum(32768);
        horizontalSlider_ExpoValue->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider_ExpoValue, 3, 3, 1, 2);

        spinBox_ExpoValue = new QSpinBox(layoutWidget);
        spinBox_ExpoValue->setObjectName(QString::fromUtf8("spinBox_ExpoValue"));
        spinBox_ExpoValue->setMaximum(32768);

        gridLayout->addWidget(spinBox_ExpoValue, 3, 5, 1, 1);

        imgchannel = new QComboBox(layoutWidget);
        imgchannel->setObjectName(QString::fromUtf8("imgchannel"));

        gridLayout->addWidget(imgchannel, 5, 4, 1, 1);

        label_8 = new QLabel(layoutWidget);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout->addWidget(label_8, 5, 3, 1, 1);

        imgdisplayer = new QLabel(centralWidget);
        imgdisplayer->setObjectName(QString::fromUtf8("imgdisplayer"));
        imgdisplayer->setGeometry(QRect(20, 210, 681, 431));
        imgdisplayer->setAutoFillBackground(false);
        imgdisplayer->setStyleSheet(QString::fromUtf8("background-color: #000"));
        IMUtext = new QPlainTextEdit(centralWidget);
        IMUtext->setObjectName(QString::fromUtf8("IMUtext"));
        IMUtext->setGeometry(QRect(460, 10, 241, 171));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 725, 20));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);
        QObject::connect(spinBox_ExpoValue, SIGNAL(valueChanged(int)), horizontalSlider_ExpoValue, SLOT(setValue(int)));
        QObject::connect(spinBox_GainValue, SIGNAL(valueChanged(int)), horizontalSlider_GainValue, SLOT(setValue(int)));
        QObject::connect(spinBox_FpgaFreq, SIGNAL(valueChanged(int)), horizontalSlider_FpgaFreq, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_FpgaFreq, SIGNAL(sliderMoved(int)), spinBox_FpgaFreq, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_ExpoValue, SIGNAL(sliderMoved(int)), spinBox_ExpoValue, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_GainValue, SIGNAL(sliderMoved(int)), spinBox_GainValue, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton_2->setText(QApplication::translate("MainWindow", "stop", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "ExpoValue", 0, QApplication::UnicodeUTF8));
        pushButton_softTrig->setText(QApplication::translate("MainWindow", "SoftTrig", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "cap", 0, QApplication::UnicodeUTF8));
        spinBox_GainValue->setPrefix(QString());
        cbAutoTrig->clear();
        cbAutoTrig->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "AutoTrig", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "SoftTrigOnce", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "FPGATrig", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "FromOutSide", 0, QApplication::UnicodeUTF8)
        );
        checkBox_AutoGain->setText(QApplication::translate("MainWindow", "Auto Gain", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "GainValue", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "TrigMode", 0, QApplication::UnicodeUTF8));
        label_7->setText(QApplication::translate("MainWindow", "HwTrigfps", 0, QApplication::UnicodeUTF8));
        checkBox_AutoExpo->setText(QApplication::translate("MainWindow", "Auto Expo", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Width", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("MainWindow", "Height", 0, QApplication::UnicodeUTF8));
        spinBox_ExpoValue->setPrefix(QString());
        imgchannel->clear();
        imgchannel->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "left", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("MainWindow", "right", 0, QApplication::UnicodeUTF8)
        );
        label_8->setText(QApplication::translate("MainWindow", "showimg", 0, QApplication::UnicodeUTF8));
        imgdisplayer->setText(QApplication::translate("MainWindow", "TextLabel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
