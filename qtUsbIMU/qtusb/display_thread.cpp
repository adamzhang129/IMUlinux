#include <display_thread.h>
#include <QTimer>
#include <pthread.h>
display_thread::display_thread(QObject * parent):QThread(parent)
{
    stop=false;
    idata=new IMUDataStruct();
    expotime=0;
    t1s=new QTimer();
    connect(t1s,SIGNAL(timeout()),this,SLOT(t1sirq()));
    t1s->start(1000);
    channel=0;
}
void display_thread::set_dispqueue(wqueue<unique_ptr<DFrameStruct> >*queue)
{
    m_queue=queue;
}
void display_thread::stopthread()
{
    stop=true;
    usleep(9999);
    m_queue->reset();
}


void display_thread::run()
{
    stop=false;
    unique_ptr<DFrameStruct> this_imageframe;
    DFrameStruct* dframethis;
    IMUDataStruct *imudata=new IMUDataStruct();
    unique_ptr<byte>uimgbuf;
    // byte* imgbuf;
    byte* imgbufLeft;
    byte* imgbufRight;
    volatile int cnt=0;
    // QImage imgcpy;
    QImage imgcpyLeft;
    QImage imgcpyRight;

    while(!stop)
    {
        this_imageframe=move(m_queue->remove());
        if(stop)
            break;

        dframethis=this_imageframe.get();
        ProcessIMUData(dframethis);
        memcpy(imudata,dframethis->IMUData.get(),sizeof(IMUDataStruct));
        // cout << channel <<endl;
        // if(channel==0)
        // {
        //     imgbuf=dframethis->leftData.get();
        // }
        // else
        // {
        //     imgbuf=dframethis->rightData.get();
        // }
        imgbufLeft = dframethis->leftData.get();
        imgbufRight = dframethis->rightData.get();

        imgLeft = QImage((const unsigned char*)imgbufLeft,
                     dframethis->width,dframethis->height,QImage::Format_Indexed8);
        imgRight = QImage((const unsigned char*)imgbufRight,
                     dframethis->width,dframethis->height,QImage::Format_Indexed8);
        
        // QImage tempImage(960, 640, QImage::Format_Mono);
        // QPainter p(&tempImage);
        // p.setCompositionMode(QPainter::CompositionMode_SourceOver);
        // p.drawImage(0, 0, imgLeft);
        // p.end();
        // p.begin(&imgRight);
        // p.drawImage(480, 0, imgRight);
        // p.end();
        

        imgcpyLeft=imgLeft.copy();
        imgcpyRight = imgRight.copy();

        // emit processedImage(imgcpy);
        emit processedImageLeft(imgcpyLeft);
        emit processedImageRight(imgcpyRight);

        if(b_t1s)
        {
            b_t1s=false;
            expotime=dframethis->expotime;
            emit sig_t1s(imudata,expotime);
        }
        usleep(10);
        //delete this_imageframe;
    }
    t1s->stop();

}
void display_thread::t1sirq()
{
    b_t1s=true;
}

int display_thread::ProcessIMUData(DFrameStruct *dFrame)
{
    int i=0;
    void *tempNum=new void*;
    IMUDataStruct *m_IMU=dFrame->IMUData.get();
    byte* m_IMUBuffer=dFrame->IMUDataBuffer.get();
    for(int j=0;j<dFrame->IMUSamplesCnt;j++)
    {
        //time Stamp
        i+=bytesToIMU(m_IMUBuffer+i,4,tempNum);
        (m_IMU+j)->timeStamp=*(unsigned int*)tempNum;
        //accel
        i+=fillAxisIMU(((IMUDataStruct*)(m_IMU+j))->accelData,m_IMUBuffer+i);
        //temperature
        i+=bytesToIMU(m_IMUBuffer+i,2,tempNum);
        (m_IMU+j)->temperData=*(short*)tempNum;
        //gyro
        i+=fillAxisIMU(((IMUDataStruct*)(m_IMU+j))->gyroData,m_IMUBuffer+i);

    }
    delete tempNum;
    return 0;
}
int display_thread::fillAxisIMU(short *imu,byte* buffer)
{
    void* tempNUM=new void*;
    int k=0;
    for(int j=0;j<3;j++,k+=2)
    {
        bytesToIMU(buffer+k,2,tempNUM,0);
        *(imu+j)=*(short*)tempNUM;
    }
    delete tempNUM;

    return k;
}
int display_thread::bytesToIMU(byte* bufbyte,int len,void* output,int outsel)//unsigned int* uiout,float *fout,int outsel=0)
{
    //float output;
    union
    {
        float fvalue;
        short uint16;
        unsigned int time;
        byte b[4];
    }utemp;

    for(int n=0;n<4;n++)
    {
        utemp.b[n]=0;
    }

    for(int i=0;i<len;i++)
    {
        byte tb=*(bufbyte+len-i-1);
        //byte tb=*(bufbyte+i);
        utemp.b[i]=tb;
    }
    /**((byte*)(&output) + 3) = b0;
    *((byte*)(&output) + 2) = b1;
    *((byte*)(&output) + 1) = b2;
    *((byte*)(&output) + 0) = b3;*/
    if(len==2)
        //*(float*)output=utemp.fvalue;
        *(short*) output=utemp.uint16;
    if(len==4)
        *(unsigned int*)output=utemp.time;
    return len;
}
int display_thread::setdispimg(int s)
{
    channel=s;
}
