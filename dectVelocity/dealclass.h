#ifndef DEALCLASS_H
#define DEALCLASS_H
#include <QThread>
#include <opencv2/opencv.hpp>
#include <QList>
#include <QMutex>
#include <QTimer>
using namespace cv;

class dealClass : public QThread
{

    Q_OBJECT
public:
    dealClass(int count);
    ~dealClass();
    void run();
    void init();
    void stop();
    const static int NormalState = 0;
    const static int NoWaterState = 1;
    const static int ExceptionState = 2;
    const static bool isDebug = false;
    const static bool isControl = false;
#pragma region 640*320->ROI{
    const static int roiWidth = 130;
    const static int roiHeight = 150;
    const static int roiX = 110;
    const static int roiY = 210;
    const static int threROI = 150;
    const static int threIsWater = 65;
#pragma endregion}
#pragma region 320*240->ROI{
//    const static int roiWidth = 130;
//    const static int roiHeight = 100;
//    const static int roiX = 50;
//    const static int roiY = 90;
//    const static int threROI = 110;
//    const static int threIsWater = 90;
#pragma endregion}
private:
    QTimer *timerSigRes;
    QList<Mat> frameL;//图像多帧列表
    int countList;//图像处理帧数
    bool stopped;//信号量,线程是否关闭
    float vel;
    QMutex mutex;
    void dealWithV();
    void dealWithV2();
    void draw_Hist(Mat img_gray);//绘制一维直方图
    Mat image_deal(Mat);//图像预处理
    double **get_feature(Mat);//提取特征
    double match_feature(Mat,Mat);//特征匹配
    double GetFunction(Mat roi);
//    QQueue<bool> isWaterFlowQ;
    bool isWaterFlow;
    float velSum;//速度的累积
    int calTimes;//每秒内计算次数
    int stateRealTimes;//每秒的铁水流状态
    bool clearDealResFun;//将dealRes函数中的静态变量以及相关变量置0的信号量
    void dealRes(const int,float);
signals:
    void sendVel(const int,float);//发送速度
    void sendSignal(bool);//可以发送帧了
    void send2Frame(Mat, Mat);
public slots:
    void recFrame(Mat,Mat);//收到插入视频帧的信号
    void recSendRes();
};

#endif // DEALCLASS_H
