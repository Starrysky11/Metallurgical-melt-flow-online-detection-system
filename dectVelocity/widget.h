#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "camclass.h"
#include "dealclass.h"
#include <QQueue>
#include <QtCharts>//图表
#include <QChartView>//图表
#include <QSplineSeries>//图表
#include <QToolButton>//下拉框
#include <QFileDialog>//对话框
#include <QJsonObject>
#include "sliderclick.h"
#include "control.h"

namespace Ui {
class Widget;
}
class itemLog
{
public:
    std::string time;
    int state;
    float q_res;
    float v_res;
    itemLog(std::string,int,float,float);
};
class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void dealDone();
private:
    Ui::Widget *ui;
    camClass *cam;
    dealClass *dealV;
    QChart *mChart;
    QChart *q_Chart;
    QChart *v_Chart;
    QLineSeries *q_LineSeries;
    QLineSeries *v_LineSeries;
    int lineCount;
    const static int lineCountMax = 60;
    bool initCamState;//初始化相机状态
    controlGPIO *gpioValve;//阀门控制
    controlGPIO *gpioLamp;//声光报警
    controlPWM *pwmGas;//气泵
//    QPixmap bkTitle,bk;
    QPixmap bk;//背景图片
    QQueue<itemLog> logQ;
    void initChart();
    virtual void paintEvent(QPaintEvent *event);
    void updateUI(itemLog);
    void clearUIPaint();
private slots:
    void recRes(const int,float);
    void recFrame(Mat);
    void recFpsSlot(int,int);
    void recSliderMoved();
//    void rec2Frame(Mat, Mat);
    void on_openCamBtn_clicked();
    void on_closeCamBtn_clicked();
    void on_clearLog();
    void on_saveLog();
    void on_loadLog();
};


#endif // WIDGET_H
