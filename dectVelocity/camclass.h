#ifndef CAMCLASS_H
#define CAMCLASS_H
#include <QThread>
#include <QTimer>
#include <opencv2/opencv.hpp>
using namespace cv;
class camClass : public QThread
{
    Q_OBJECT
public:
    camClass();//构造函数
    ~camClass();//析构函数
    void run();//线程的主函数
    void stop();//停止线程运行
    bool camINit();//相机初始化
private:
    QTimer *timer;//定时器
    QTimer *fpsTimer;//记录帧率的定时器
    Mat frame;//图像帧
    VideoCapture capture;
    bool stopped;//信号量,线程是否关闭
    volatile bool sendimg_s;
    bool send2Deals;
    bool sendFps;
    int showFps;
    int capFps;
signals://信号
    void sendFrame(Mat);
    void send2Deal(Mat,Mat);
    void sendRes(float);
    void sendFpsSignal(int,int);
public slots://槽函数
    void recMess();
    void recSendFrame();
    void recDealSignal(bool);
    void recFpsSlot();
};

#endif // CAMCLASS_H
