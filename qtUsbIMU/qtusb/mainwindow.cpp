#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <vector>
#include <QDebug>


#include <ros/ros.h>
#include <sstream>
#include "std_msgs/String.h"

#include <image_transport/image_transport.h>

#include <opencv2/highgui/highgui.hpp>


typedef unsigned char byte;

CDataCapture *m_pDataCapture;
extern int g_width;
extern int g_height;
extern long ReadDataBytes;

enum ReqValue
{
    TRIGMODE=0xD0,IMGDISP,EXPOGAIN,GAIN,EXPO,MIRROR,RCEXTR,TRIGPERIOD,RSTHW,SOFTTRIG,RSTSENSOR
};


MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    qDebug() << Q_FUNC_INFO;

    ui->setupUi(this);
    h1=NULL;
    //bool ok;
   // unsigned int temp=ui->lineEdit_ExpoValue->text().toUInt(&ok,16);
    ui->lineEdit_Height->setText("480");
    ui->lineEdit_Width->setText("640");
    ui->cbAutoTrig->setCurrentIndex(0);
    t1s=new QTimer(this);
    m_pDataCapture=new CDataCapture();
    this_displaythx=new display_thread();
    connect(ui->horizontalSlider_ExpoValue,SIGNAL(sliderReleased()),this,SLOT(setExpoValue()));
    connect(ui->horizontalSlider_FpgaFreq,SIGNAL(sliderReleased()),this,SLOT(setFpgaFreq()));
    connect(ui->horizontalSlider_GainValue,SIGNAL(sliderReleased()),this,SLOT(setGainValue()));
    connect(ui->spinBox_ExpoValue,SIGNAL(valueChanged(int)),this,SLOT(setExpoValue()));
    connect(ui->spinBox_FpgaFreq,SIGNAL(valueChanged(int)),this,SLOT(setFpgaFreq()));
    connect(ui->spinBox_GainValue,SIGNAL(valueChanged(int)),this,SLOT(setGainValue()));
    connect(ui->checkBox_AutoExpo,SIGNAL(released()),this,SLOT(setAutoGainExpo()));
    connect(ui->checkBox_AutoGain,SIGNAL(released()),this,SLOT(setAutoGainExpo()));


    connect(this_displaythx, SIGNAL(processedImageLeft(QImage)), this, SLOT(updatePlayerUI(QImage)));
    connect(this_displaythx, SIGNAL(processedImageRight(QImage)), this, SLOT(updateRightImage(QImage)));
    connect(this_displaythx,SIGNAL(sig_t1s(IMUDataStruct*,uint)), this,SLOT(upadateIMUText(IMUDataStruct*,uint)));
}

void MainWindow::upadateIMUText(IMUDataStruct*is,uint et)
{
    IMUDataStruct*m_IMU=is;
   unsigned int expotime=et;
    //ui->IMUtext->document()->clear();

    QString text=QString("Accel      Gyro \n X:%1    |%2\nY:%3    |%4\nZ:%5    |%6\nExpoTime(us):%7").arg(
                QString::number(m_IMU->accelData[0]),QString::number(m_IMU->gyroData[0]),
                QString::number(m_IMU->accelData[1]),QString::number(m_IMU->gyroData[1]),
                QString::number(m_IMU->accelData[2]),QString::number(m_IMU->gyroData[2]),
                QString::number(expotime*27.185)
            );
    ui->IMUtext->document()->setPlainText(text);
    m_IMU2ROS = is;
}

void MainWindow::updatePlayerUI(QImage img)
{
    //qDebug() << Q_FUNC_INFO;
    if (!img.isNull())
    {
        ui->imgdisplayer->setAlignment(Qt::AlignCenter);
        ui->imgdisplayer->setPixmap(QPixmap::fromImage(img).scaled(ui->imgdisplayer->size(),
                                           Qt::KeepAspectRatio, Qt::FastTransformation));

        img2ROSLeft = img.copy();
        
    }
}

void MainWindow::updateRightImage(QImage img){

    if (!img.isNull())
    {

        img2ROSRight = img.copy();
        
    }
}

// void MainWindow::getImage2ROS(QImage img)
// {
//     // if(!img.isNull())
//     // {
//     //     cv::Mat  mat( img.height(), img.width(),
//     //                 CV_8UC1,
//     //                 const_cast<uchar*>(img.bits()),
//     //                 static_cast<size_t>(img.bytesPerLine())
//     //                 );
//     //     cvImage = mat;
//     // }
// }

MainWindow::~MainWindow()
{
       f_capture=false;
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

    f_capture=false;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(f_capture)
        return;
    f_capture=true;

    int r=cyusb_open();
    int usbNum=0;//s_usbNum.toInt();
    if(r<0)
    {
        ui->statusBar->showMessage("error opening lib");
        cyusb_close();
    return;
    }
    else if(r==0)
    {
        ui->statusBar->showMessage("no device found");
        cyusb_close();
        return;
    }
    t1s->start(1000);
        h1=cyusb_gethandle(usbNum);
        r=cyusb_kernel_driver_active(h1,0);
        if(r!=0)
        {
            ui->statusBar->showMessage("kernel driver active, exitting");
            cyusb_close();
            return;
        }
       // r = cyusb_claim_interface(h1, 0);
        if ( r != 0 ) {
            ui->statusBar->showMessage("Error in claiming interface\n\t");
            cyusb_close();
            return ;
        }

    g_width=ui->lineEdit_Width->text().toInt();
    g_height=ui->lineEdit_Height->text().toInt();
    if(ReadDataBytes==0)
    {
        ui->statusBar->showMessage("height and width error");
        return;
    }
    m_pDataCapture->Open(this_displaythx,h1);
    m_pDataCapture->start();
    m_pDataCapture->setPriority(QThread::HighestPriority);
}
void MainWindow::on_pushButton_2_clicked()
{
    if(f_capture==false)
        return;
    f_capture=false;
    m_pDataCapture->Close();
    t1s->stop();
    //cyusb_close();
}

void MainWindow::on_cbAutoTrig_currentIndexChanged(int index)
{
    memset(data,0,2);
    data[0]=index&0xff;
    //data[1]=
    if(index==2)
    {
        int freq=ui->spinBox_FpgaFreq->value();
        if(freq==0)
        {
            ui->statusBar->showMessage("FPGA Freq Required");
        }
        data[1]=freq;
    }
    if(h1!=NULL)
    cyusb_control_write(h1,0x40,0xd0,0,0,data,2,100);
}

void MainWindow::on_pushButton_softTrig_clicked()
{
    int r=-1;
    data[0]=0x01;
    data[1]=0;
     //r=cyusb_control_transfer(h1,0x40,0xD0,0,0,data,2,100);
     //r=cyusb_control_transfer(h1,0x40,0xD9,0,0,0,0,100);
    if(h1!=NULL)
    //r=cyusb_control_write(h1,0x40,0xd0,0,0,data,2,100);
    r=cyusb_control_write(h1,0x40,0xd9,0,0,0,0,100);
    if(r!=0)
    {
        ui->statusBar->showMessage(QString::number(r));
    }
}

//void MainWindow::on_pushButton_FpgaTrigFreq_clicked()
//{
//    if(h1!=NULL)
//    cyusb_control_read(h1,0x40,TRIGPERIOD,0,0,data,1,100);
//    QString temp=QString::number(data[0]);
//    ui->statusBar->showMessage(temp);
//}

void MainWindow::setFpgaFreq()
{
    int freq=ui->spinBox_FpgaFreq->value();
    if(freq>0&&(ui->cbAutoTrig->currentIndex()==2))
    {
        data[0]=2;
        data[1]=freq&0xff;
        if(h1!=NULL)
        cyusb_control_write(h1,0x40,TRIGMODE,0,0,data,2,100);
        return;
    }
    else
    {
        ui->statusBar->showMessage("Check Index and Freq Input");
    }
}
void MainWindow::setExpoValue()
{
    int expo=ui->spinBox_ExpoValue->value();
    if(expo>=0&&(!ui->checkBox_AutoExpo->isChecked()))
    {
        data[0]=(expo&0xff<<8)>>8;
        data[1]=expo&0xff;
        if(h1!=NULL)
        cyusb_control_transfer(h1,0x40,EXPO,0,0,data,2,100);
    }
    else
    {
        ui->statusBar->showMessage("check Expo?");
    }
    return;
}
void MainWindow::setGainValue()
{
    int gain=ui->spinBox_GainValue->value();
    if(gain>=0&&(!ui->checkBox_AutoGain->isChecked()))
    {
        data[0]=gain;
        if(h1!=NULL)
        cyusb_control_transfer(h1,0x40,GAIN,0,0,data,1,100);

    }
    else
    {
        ui->statusBar->showMessage("check Gain?");
        return;
    }

}
void MainWindow::setAutoGainExpo()
{
    data[0]=ui->checkBox_AutoExpo->isChecked()==true?1:0;
    data[0]+=(ui->checkBox_AutoGain->isChecked()==true?1:0)<<1;
    if(h1!=NULL)
    cyusb_control_transfer(h1,0x40,EXPOGAIN,0,0,data,1,100);
}

void MainWindow::on_imgchannel_currentIndexChanged(int index)
{
    this_displaythx->setdispimg(index);
}
