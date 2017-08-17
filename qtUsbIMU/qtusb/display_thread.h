#ifndef DISPLAY_THREAD_H
#define DISPLAY_THREAD_H
#include "imgframe.h"
#include "wqueue.h"
#include <QThread>
#include <QImage>
#include<QTimer>
#include <memory>
using namespace std;
class display_thread:public QThread//public QObject,public QThread
{
    Q_OBJECT


private:
    QImage img;
    bool stop;
    pthread_mutex_t  m_mutex;
    wqueue<unique_ptr<DFrameStruct> >*m_queue;
    void putframe(DFrameStruct* sf);
    QTimer *t1s;
    int ProcessIMUData(DFrameStruct *dFrame);
    int fillAxisIMU(short *imu,byte* buffer);
    int bytesToIMU(byte* bufbyte,int len,void* output,int outsel=0);
    //wqueue<imgFrame*> m_queue;
    int channel;
signals:
    void processedImage(const QImage image);
    void sig_t1s(IMUDataStruct *is,unsigned int et);
private slots:
    void t1sirq();
    //void processedImage(imgFrame * this_imgframe);
public:
    display_thread(QObject *parent = 0);
   void set_dispqueue(wqueue<unique_ptr<DFrameStruct> >*queue);
    void stopthread();
    void getframe(IMUDataStruct *destframe,unsigned int *et);
    bool b_t1s;
    IMUDataStruct *idata;
   unsigned int expotime;
   int setdispimg(int s);
protected:
    void run();
};

#endif // DISPLAY_THREAD_H
