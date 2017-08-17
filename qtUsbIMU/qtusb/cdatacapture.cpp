#include "cdatacapture.h"
#include <unistd.h>
#include <QDebug>

int g_width=640;
int g_height=480;
long ReadDataBytes=1024*1024*4;

CDataCapture::CDataCapture():QThread()
{
    std::unique_ptr<byte*> test;
    m_iCount=0;
    m_iRowIndex=0;
    m_bFindDbFive=FALSE;
    m_pInData=NULL;
    m_pOutData=NULL;
    m_pReadBuff=NULL;
    f_capture=true;
    b_header=false;
    b_imu=false;
}
void CDataCapture::run()
{

    int r=cyusb_open();
    int usbNum=0;//s_usbNum.toInt();
    if(r<0)
    {
        qDebug()<<"error opening lib";
        cyusb_close();
    return ;
    }
    else if(r==0)
    {
        qDebug()<<"no device";
        cyusb_close();
        return ;
    }
        h2=cyusb_gethandle(usbNum);
        r=cyusb_kernel_driver_active(h2,0);
        if(r!=0)
        {
            qDebug()<<"kernel driver active, exitting";
            cyusb_close();
            return ;
        }
        r = cyusb_claim_interface(h2, 0);
        if ( r != 0 ) {
            qDebug()<<"Error in claiming interface";
            cyusb_close();
            return ;
        }
    int transferred=0;
    unsigned char data[4];
    data[0]=(g_width&0xff<<8)>>8;
    data[1]=g_width&0xff;
    data[2]=(g_height&0xff<<8)>>8;
    data[3]=g_height&0xff;
    //cyusb_control_write(h2,0x40,0xD1,0,0,data,4,100);
    while (f_capture) {
        //if(cv::waitKey(1)=='e')break;

        r = cyusb_bulk_transfer(h2, 0x86, m_pReadBuff, ReadDataBytes, &transferred,1);
        if(transferred>=0)
        {
            Input(m_pReadBuff,transferred);
        }
        //usleep(1);
    }
    if(m_pOutData!=NULL)
    {
        delete[] m_pOutData;
        //m_pOutData=NULL;
    }
    if(m_pInData!=NULL)
    {
        delete[] m_pInData;
        //m_pInData=NULL;
    }
    cyusb_close();
    h2=NULL;
}

int CDataCapture::Open(display_thread *dispx,cyusb_handle *ch)
{
    f_capture=true;

    m_pInData=new byte[(ReadDataBytes*2)];
    m_pReadBuff=new byte[ReadDataBytes];
    memset(m_pInData,0,(ReadDataBytes+g_width+3)*sizeof(byte));

    thread1 = dispx;//new display_thread(queue);
    disqueue=new wqueue<unique_ptr<DFrameStruct> >();
    thread1->set_dispqueue(disqueue);
    thread1->start();
    return 0;
}

int CDataCapture::Close()
{
    if(f_capture==false)
        return -1;
    f_capture=false;
    usleep(9999);
    //delete &queue;
    thread1->stopthread();
    //thread1->join();

    return 0;
}

int CDataCapture::Input( byte* lpData,unsigned int dwSize )
{
    int iBytes=0;
        iBytes=dwSize+m_iCount;//m_iCount上一次拷贝剩余数据
        memcpy(m_pInData+m_iCount,lpData,dwSize);
        bool b_header=false,b_imu=false;
        for(int i=0;i<iBytes;++i)
        {
            int imulen=0;
            if ((i + g_width * g_height * 3) >= iBytes)//如果剩下的最后几个数据长度小于video_width*2+2行号个，不足以构成完整一行，拷贝到下一缓存
                {
                    m_iCount = iBytes - i;
                    memcpy(m_pInData, m_pInData + i, m_iCount);
                    return 0;
                }
            if(m_pInData[i]==0x33&&m_pInData[i+1]==0xcc&&m_pInData[i+14]==0x22&&m_pInData[i+15]==0xdd&&b_header==FALSE)
            {
                dFrame.reset(new DFrameStruct);
                uint tempet=m_pInData[i+2]<<8;
                tempet+=m_pInData[i+3];
                (*dFrame).expotime=tempet;
                (*dFrame).imgCnt=m_pInData[i+4];
                (*dFrame).IMUSamplesCnt=m_pInData[i+5];
                imulen=dFrame->IMUSamplesCnt*dFrame->IMUSampleLength;
                //(*dFrame).IMUPresent=m_pInData[i+5];
                unsigned int temp=m_pInData[i+6]<<8;
                temp=temp+m_pInData[i+7];
                (*dFrame).height=temp;
                temp=m_pInData[i+8]<<8;
                temp+=m_pInData[i+9];
                (*dFrame).width=temp;//(m_pInData[i+8]<<8+m_pInData[i+9]);

                (*dFrame).timestamp=m_pInData[i+10]<<8*3+m_pInData[i+11]<<8*2+m_pInData[i+12]<<8+m_pInData[i+13];
                dFrame->IMUData.reset(new IMUDataStruct[dFrame->IMUSamplesCnt]);
                dFrame->IMUDataBuffer.reset(new byte[imulen]);
                dFrame->leftData.reset(new byte[dFrame->height*dFrame->width]);
                dFrame->rightData.reset(new byte[dFrame->height*dFrame->width]);
                m_pOutDataLeft=dFrame->leftData.get();
                m_pOutDataRight=dFrame->rightData.get();
                m_pIMU=dFrame->IMUDataBuffer.get();
                i+=16;
                b_header=true;
            }
            if(m_pInData[i]==0x66&&m_pInData[i+1]==0xdd&&m_pInData[i+imulen+2]==0x44&&m_pInData[i+imulen+3]==0xbb&&b_header)
            {
                memcpy(m_pIMU,m_pInData+i+2,imulen);
                i+=imulen+4;
                b_imu=true;
            }
            else if(b_header==true&&m_bFindDbFive==false)
            {
                b_header=false;
                b_imu=false;
            }

            if (b_header&&b_imu)
            {

                unsigned int datalen = dFrame->width * dFrame->height;
                memcpy(m_pOutDataLeft, m_pInData + i, datalen);
                memcpy(m_pOutDataRight, m_pInData + i + datalen, datalen);
                //m_pDataProcess->Input(dFrame, (*dFrame).width * (*dFrame).height);
                disqueue->add(move(dFrame));
                b_imu = false;
                b_header = false;
                m_bFindDbFive = false;
                i = i + datalen*2-1;
            }

        }//for
        return 0;
}
