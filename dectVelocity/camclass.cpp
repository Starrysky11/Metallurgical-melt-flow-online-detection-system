#include "camclass.h"

camClass::camClass()
{
    this->stopped = false;
    this->sendimg_s = false;
    this->send2Deals = false;
    timer = new QTimer(this);//打开相机
    fpsTimer = new QTimer(this);//统计帧率的定时器
    connect(timer, SIGNAL(timeout()), this, SLOT(recSendFrame()));
    connect(fpsTimer, SIGNAL(timeout()), this, SLOT(recFpsSlot()));
}
void camClass::run()
{
    int capFps = 0;
    int showFps = 0;
    int count = 0;
    Mat lastFrame,nowframe;
    while(!this->stopped)
    {
        capture>>this->frame;
        capFps++;
        if(this->sendimg_s == true)
        {
            showFps++;
            this->sendimg_s = false;
            emit sendFrame(frame);//发送信号
        }
        if(this->send2Deals == true)
        {
            if(count == 0)
            {
                lastFrame = this->frame;
                count++;
            }
            else if(count == 1)
            {
                nowframe = this->frame;
                count = 0;
                emit send2Deal(lastFrame,nowframe);
            }

        }
        if(this->sendFps == true)
        {
            this->sendFps = false;
            this->capFps = capFps;
            this->showFps = showFps;
            capFps = 0;
            showFps = 0;
            emit sendFpsSignal(this->capFps,this->showFps);
        }
        this->frame.release();
    }
}
bool camClass::camINit()
{
    if(!capture.isOpened())//如果相机没有打开过的话
    {//设置相机
        capture.open(0);//打开相机
        if(!capture.isOpened())
            return false;
        capture.set(CAP_PROP_FPS,200);
        capture.set(CAP_PROP_FRAME_WIDTH, 640);//640
        capture.set(CAP_PROP_FRAME_HEIGHT, 400);//400
//        capture.set(CV_CAP_PROP_EXPOSURE,-10);//曝光设置
    }
    this->stopped = false;
    timer->start(33);
    fpsTimer->start(1000);
    return true;
}
void camClass::recSendFrame()
{
    this->sendimg_s = true;
}
void camClass::recFpsSlot()
{
    this->sendFps = true;
}
void camClass::recMess()
{
    emit sendRes(1.5);
}
void camClass::recDealSignal(bool signal)
{
    this->send2Deals = signal;
}
void camClass::stop()
{
    this->stopped = true;
    timer->stop();
    fpsTimer->stop();
}
camClass::~camClass()
{
    this->stopped = true;
    timer->stop();//关闭定时器
    fpsTimer->stop();//关闭帧率定时器
    capture.release();//关闭相机
}
