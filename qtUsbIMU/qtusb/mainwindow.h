#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../../cyusb_linux_1.0.4/include/cyusb.h"
#include "cdatacapture.h"
#include <display_thread.h>
#include <QTimer>




namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    
    QImage img2ROSLeft;
    QImage img2ROSRight;
    IMUDataStruct*m_IMU2ROS;
void closeEvent(QCloseEvent *event);
protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;

        unsigned char *data=new unsigned char[4];
        display_thread *this_displaythx;
        cyusb_handle *h1;
        volatile bool f_capture=false;
        QTimer *t1s;
// public slots:
    // void getImage2ROS(QImage img);
private slots:
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();
    void on_cbAutoTrig_currentIndexChanged(int index);
    void on_pushButton_softTrig_clicked();
    //void on_pushButton_FpgaTrigFreq_clicked();
    void setFpgaFreq();
    void setExpoValue();
    void setGainValue();
    void setAutoGainExpo();
    void updatePlayerUI(QImage img);
    void upadateIMUText(IMUDataStruct*is,uint et);

    void on_imgchannel_currentIndexChanged(int index);

    void updateRightImage(QImage img);


    
};

#endif // MAINWINDOW_H
