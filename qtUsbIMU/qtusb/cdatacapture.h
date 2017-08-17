#ifndef CDATACAPTURE_H
#define CDATACAPTURE_H
#include <QGraphicsScene>
#include <QGraphicsView>
#include <qstring.h>
#include <string>
#include <stdint.h>
#include <string.h>
#include "display_thread.h"
#include "imgframe.h"
#include "../../cyusb_linux_1.0.4/include/cyusb.h"
#include <QThread>
#include <memory>
typedef unsigned char byte;
class CDataCapture:public QThread
{

public:
    CDataCapture();
    display_thread* thread1;
    int Open(display_thread *dispx,cyusb_handle *ch);//CDataProcess *pProcess);
    int Close();
    int Input( byte* lpData,unsigned int dwSize );
    void run();

    //int GetFrame(byte *m_pInData,unsigned long pointer,unsigned long len,int Cam_Num);
private:
    int			m_iCount;		//数据计数器
    int			m_iRowIndex;	//行索引
    bool        m_bFindDbFive;	//标记是否找到55
    byte*		m_pInData;		//接收数据缓冲
    byte*		m_pOutData;		//输出数据缓冲
    byte* m_pOutDataLeft;
    byte* m_pOutDataRight;
    byte* m_pIMU;
    std::string wname;
    //wqueue<imgFrame*>  *disqueue;
    //imgFrame *inputframe;
    wqueue<unique_ptr<DFrameStruct> >*disqueue;
    cyusb_handle *h2;
    bool f_capture;
    byte *m_pReadBuff;
    int lastRowIdx;
    bool b_header;
    bool b_imu;
    std::unique_ptr<DFrameStruct> dFrame;

};

#endif // CDATACAPTURE_H
