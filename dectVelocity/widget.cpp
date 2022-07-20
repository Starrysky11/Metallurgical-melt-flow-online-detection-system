#include "widget.h"
#include "ui_widget.h"
#include <QMetaType>
#include <QTimer>
#include <QPainter>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
#pragma region 背景设置{
    //不显示标题栏，亦无边框
//    setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
    setWindowFlags(Qt::Window);
    //设置背景（全透明）
    setAttribute(Qt::WA_TranslucentBackground);
    initChart();
    qRegisterMetaType<cv::Mat>("Mat");//注册Mat到消息队列中
    bk.load(":/new/pic/bk.jpg");
#pragma endregion}
#pragma region toolButton按钮设置{
    QMenu *menu = new QMenu();
//    menu.addAction()
    QAction *clearLog = new QAction(menu);
    QAction *saveLog = new QAction(menu);
    QAction *loadLog = new QAction(menu);
    clearLog->setText("清空日志");
    saveLog->setText("保存日志");
    loadLog->setText("加载日志");
    menu->addAction(saveLog);
    menu->addAction(loadLog);
    menu->setMinimumSize(100,50);
    menu->setMaximumSize(100,50);
//    menu->sizeHint();
    menu->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    menu->setStyleSheet("QMenu::item{padding-left:10px;padding-bottom:2px;}");
    ui->toolButton->setDefaultAction(clearLog);//设置默认Action
    ui->toolButton->setMenu(menu);//设置下拉菜单
#pragma endregion}
#pragma region slider设置{
    //slider最大最小值
    ui->timeSlider->setMinimum(0);
    ui->timeSlider->setMaximum(lineCountMax);
    ui->timeSlider->setSingleStep(1);
    ui->timeSlider->setEnabled(false);
    // 设置是否启动滑块追踪：true 表示启动追踪；false 表示禁用追踪；
     // 如果启用了滑块追踪，则滑块在拖动过程中会一直触发 valueChanged 信号；
     // 如果禁用了滑块追踪，则滑块在拖动过程中不会触发 valueChanged 信号，
     // 只有在用户释放滑块时，才触发 valueChanged 信号。
    ui->timeSlider->setTracking(true);
#pragma endregion}

    cam = new camClass;
    dealV = new dealClass(2);
    this->initCamState = false;//未初始化相机
    if(dealClass::isControl == true)
    {
        gpioValve = new controlGPIO(37);//阀门
        gpioLamp = new controlGPIO(38);//灯光报警
        pwmGas = new controlPWM(1);//气泵
        pwmGas->set_duty(0);
    }
    connect(cam,&camClass::sendFrame, this, &Widget::recFrame);
    connect(cam,&camClass::send2Deal, dealV, &dealClass::recFrame);
    connect(cam,&camClass::sendFpsSignal,this,&Widget::recFpsSlot);
    connect(dealV, &dealClass::sendVel, this, &Widget::recRes);
    connect(dealV, &dealClass::sendSignal, cam, &camClass::recDealSignal);
    //当按窗口右上角x时，触发destroyed信号
    connect(this, &Widget::destroyed, this, &Widget::dealDone);
    //QAction 绑定事件 处理日志
    connect(clearLog,SIGNAL(triggered()),this,SLOT(on_clearLog()));
    connect(saveLog,SIGNAL(triggered()),this,SLOT(on_saveLog()));
    connect(loadLog,SIGNAL(triggered()),this,SLOT(on_loadLog()));

    connect(ui->timeSlider,&QSlider::valueChanged,this,&Widget::recSliderMoved);
}
void Widget::on_clearLog()
{
    clearUIPaint();
}
void Widget::on_saveLog()
{

    QString fileName = QFileDialog::getSaveFileName(this,tr("保存日志"),"testLog",tr("数据格式(*.json)"));
    fileName += ".json";
    if(dealClass::isDebug == true)
        qDebug()<<"filename:"<<fileName;
    if(fileName.isNull())//如果文件名为空，直接结束
        return;
    QJsonObject *jsonObject = new QJsonObject();

    QFile srcFile(fileName);
    if(!srcFile.open(QFile::ReadWrite))
    {
        //文件打开失败,提示
        QMessageBox msgBox;
        msgBox.setWindowTitle("打开异常");
        msgBox.setText("文件打开失败!");
        msgBox.exec();
        return;
    }
    QTextStream in(&srcFile);
    QJsonArray jsonArray;
    for(int i = 0; i < logQ.size(); ++i)
    {
        //构造一个QJsonObject类型的数据
        QJsonObject jsonObject;
        jsonObject.insert("时间",QString::fromStdString(logQ.at(i).time));
        jsonObject.insert("状态",logQ.at(i).state);
        jsonObject.insert("流量q",logQ.at(i).q_res);
        jsonObject.insert("流量v",logQ.at(i).v_res);
        jsonArray.append(jsonObject);//将Object类型的数据添加到json数组中
    }
    QJsonDocument document;
    document.setArray(jsonArray);
    QByteArray byteArray = document.toJson(QJsonDocument::Compact);
    QString str(byteArray);
    in<<str;
}
void Widget::on_loadLog()
{
    //获取加载日志文件
    QString fileName = QFileDialog::getOpenFileName(this,tr("加载日志"),"./",tr("All Files(*.json)")); //"数据格式(*json)"
    QFile srcFile(fileName);
    if(!srcFile.open(QFile::ReadWrite)){
        //文件打开失败,提示
        QMessageBox msgBox;
        msgBox.setWindowTitle("打开异常");
        msgBox.setText("文件打开失败!");
        msgBox.exec();
        return;
    }
    QJsonParseError error;
    QJsonDocument doucment = QJsonDocument::fromJson(srcFile.readAll(), &error);
    if (!doucment.isNull() && (error.error == QJsonParseError::NoError)) { //解析否出现错误
        if (doucment.isArray()) { // 数组判断
            QJsonArray array = doucment.array();  // 转数组
            this->clearUIPaint();//ui清空，清空原来的数据
            for(int i = 0; i < array.count(); i++)
            {
                // 通过 QJsonArray::at(i)函数获取数组下的第i个元素
                QJsonValue locationArray = array.at(i);
                // qDebug() << locationArray;
                // 通过 QJsonValue::toObject()函数将数组元素转换成Object对象
                QJsonObject jsonObj = locationArray.toObject();
                itemLog *item = new itemLog(jsonObj.value("时间").toString().toStdString(),
                                           jsonObj.value("状态").toInt(),
                                           jsonObj.value("流量q").toDouble(),
                                           jsonObj.value("流量v").toDouble());
                logQ.enqueue(*item);
                updateUI(*item);
            }
        }
    }
}
void Widget::paintEvent(QPaintEvent *event)//设置背景
{
    QPainter painter(this);
    QRect frameRect = rect();
    frameRect.adjust(0,0,0,0);
    painter.setPen(QColor(0,0,0));
    painter.setBrush(QColor(255,255,255));
    painter.drawRoundRect(frameRect, 2, 2);
    painter.drawPixmap(frameRect,bk);
}
void Widget::initChart()
{
    //已经绘制的点数为0
    this->lineCount = 0;
    //坐标轴
    QValueAxis *q_axisX = new QValueAxis();
    QValueAxis *q_axisY = new QValueAxis();
    QValueAxis *v_axisX = new QValueAxis();
    QValueAxis *v_axisY = new QValueAxis();
    //设定x轴最大最小值
    q_axisX->setMax(lineCountMax);
    v_axisX->setMax(lineCountMax);
    q_axisX->setMin(0);
    v_axisX->setMin(0);


    //设定y轴最大最小值
    q_axisY->setMax(1);//1
    v_axisY->setMax(40);//20
    q_axisY->setMin(0);
    v_axisY->setMin(0);

    //x轴坐标轴单位格式->整数类型
    q_axisX->setLabelFormat("%d");
    v_axisX->setLabelFormat("%d");

    {
        q_axisX->setTitleText(QStringLiteral("时间(s)"));
        QChar ch(0x00B3);//3的上标
        QString *stry = new QString("流量(m");
        stry->push_back(ch);
        stry->append("/s)");
//        q_axisY->setTitleText(*stry);
    }

    {
        v_axisX->setTitleText(QStringLiteral("时间(s)"));
        QChar ch(0x00B3);//3的上标
        QString *stry = new QString("累积流量(m");
        stry->push_back(ch);
        stry->append(")");
//        v_axisY->setTitleText(*stry);
    }

    q_axisX->setGridLineVisible(false); //隐藏背景网格x轴框线
    q_axisY->setGridLineVisible(false); //隐藏背景网格y轴框线
    v_axisX->setGridLineVisible(false); //隐藏背景网格x轴框线
    v_axisY->setGridLineVisible(false); //隐藏背景网格y轴框线

    //图表对象
    q_Chart = new QChart();
    v_Chart = new QChart();

    q_Chart->addAxis(q_axisX,Qt::AlignBottom);//将X轴添加到图表上
    q_Chart->addAxis(q_axisY,Qt::AlignLeft);//将Y轴添加到图表上
    v_Chart->addAxis(v_axisX,Qt::AlignBottom);//将X轴添加到图表上
    v_Chart->addAxis(v_axisY,Qt::AlignLeft);//将Y轴添加到图表上

    //设置图表主题
//    q_Chart->setTheme(QChart::ChartThemeDark);
//    v_Chart->setTheme(QChart::ChartThemeDark);
    QFont *font = new QFont("宋体",8,true);
    font->setBold(true);
    //设置label颜色
    q_Chart->axisX()->setLabelsColor(Qt::white);
    //设置title颜色
    q_Chart->axisX()->setTitleBrush(QBrush(Qt::white));
    //同上
    q_Chart->axisY()->setLabelsColor(Qt::white);
    q_Chart->axisY()->setTitleBrush(QBrush(Qt::white));
    //设置字体
    q_Chart->axisX()->setTitleFont(*font);
    q_Chart->axisY()->setTitleFont(*font);
    //同上
    v_Chart->axisX()->setLabelsColor(Qt::white);
    v_Chart->axisX()->setTitleBrush(QBrush(Qt::white));
    v_Chart->axisY()->setLabelsColor(Qt::white);
    v_Chart->axisY()->setTitleBrush(QBrush(Qt::white));
    v_Chart->axisX()->setTitleFont(*font);
    v_Chart->axisY()->setTitleFont(*font);
    //设置背景颜色
    QColor color(38,38,48);
    color.setAlpha(200);
    q_Chart->setBackgroundBrush(QBrush(color));
    v_Chart->setBackgroundBrush(QBrush(color));

    q_Chart->layout()->setContentsMargins(0,0,0,0);//设置外边界全部为0
    q_Chart->setMargins(QMargins(0,0,0,0));//设置内边界全部为0
    q_Chart->setBackgroundRoundness(0);//设置背景区域无圆角

    //创建曲线对象
    q_LineSeries = new QLineSeries();
    v_LineSeries = new QLineSeries();
    q_LineSeries->setPointsVisible(true);
    v_LineSeries->setPointsVisible(true);

    q_Chart->addSeries(q_LineSeries);// 将曲线对象添加到图表上
    q_Chart->setAnimationOptions(QChart::SeriesAnimations);// 动画：能使曲线绘制显示的更平滑，过渡效果更好看
    v_Chart->addSeries(v_LineSeries);// 将曲线对象添加到图表上
    v_Chart->setAnimationOptions(QChart::SeriesAnimations);// 动画：能使曲线绘制显示的更平滑，过渡效果更好看


    //设置曲线对象,将曲线对象关联到坐标轴上
    q_LineSeries->attachAxis(q_axisX);
    q_LineSeries->attachAxis(q_axisY);
    v_LineSeries->attachAxis(v_axisX);
    v_LineSeries->attachAxis(v_axisY);

    //设置图表边界
    v_Chart->layout()->setContentsMargins(0,0,0,0);//设置外边界全部为0
    v_Chart->setMargins(QMargins(0,0,0,0));//设置内边界全部为0
    v_Chart->setBackgroundRoundness(0);//设置背景区域无圆角

    //隐藏图表图例
    q_Chart->legend()->hide();
    v_Chart->legend()->hide();

    //将图表对象关联到graphicsView上进行绘制
    ui->showQChart->setChart(q_Chart);
    ui->showVChart->setChart(v_Chart);

    //设置渲染：抗锯齿
    ui->showQChart->setRenderHints(QPainter::Antialiasing);
    ui->showVChart->setRenderHints(QPainter::Antialiasing);
}
void Widget::on_openCamBtn_clicked()
{
    this->initCamState = true;
    if(!cam->camINit())
    {
        //相机打开失败,提示
        QMessageBox msgBox;
        msgBox.setWindowTitle("相机异常");
        msgBox.setText("相机打开失败！请检查相机是否连接。");
        msgBox.exec();
        return;
    }
    dealV->init();
    if(!cam->isRunning())
        cam->start();
    if(!dealV->isRunning())
        dealV->start();
    ui->openCamBtn->setEnabled(false);
}
void Widget::on_closeCamBtn_clicked()
{
    dealDone();
    ui->camVideo->clear();
    this->initCamState = false;
    ui->openCamBtn->setEnabled(true);
}
#pragma region 槽函数{
/*函数功能：显示图像
  函数入口：frame(图像)
*/
void Widget::recFrame(Mat frame)
{
    QImage disImage = QImage((uchar*)(frame.data), frame.cols, frame.rows, QImage::Format_RGB888);
    if(dealClass::isDebug == true)
    {
        QPainter pp(&disImage);
        pp.setPen(QPen(Qt::red,3));//设置画笔颜色：Qt::red,粗细：3
        pp.drawRect(dealClass::roiX,dealClass::roiY,dealClass::roiWidth,dealClass::roiHeight);
    }
    //Qt::KeepAspectRatio 保持图片比例
    ui->camVideo->setPixmap(QPixmap::fromImage(disImage.scaled(ui->camVideo->size(), Qt::KeepAspectRatio)));
//    ui->camVideo->resize(disImage.size());
    ui->camVideo->show();
    if(this->initCamState == false)
    {
        ui->camVideo->clear();
    }
}

void Widget::recFpsSlot(int capFps, int showFps)
{
    static int counts = 0;
    if(dealClass::isControl == true)
    {
        ++counts;
        if(counts > 240)
        {
            pwmGas->set_duty(0.4);
        }
    }
    ui->capFPSText->setText(QString::number(capFps)+"fps");
    ui->showFPSText->setText(QString::number(showFps)+"fps");
}
void Widget::recRes(const int ironWaterState, float res)
{
    static float Q2V = 0;
    //限幅 & 处理数据
    res = (res > 39.1f) ? 39.1f : res;
    Q2V = (Q2V+res > 95)?95:Q2V + res*0.0071f;//计算累积流量
    res = res*0.02556f;//计算实时流量
    //获取时间
    QDateTime current_date_time = QDateTime::currentDateTime();
    QString timeStr = current_date_time.toString("yyyy.MM.dd.hh:mm:ss");
    itemLog *item = new itemLog(timeStr.toStdString(),ironWaterState,res,Q2V);
    if(dealClass::isControl == true && ironWaterState == 2)
    {
        gpioLamp->setHigh();//打开声光报警
        gpioValve->setLow();//关闭阀门
    }
    logQ.enqueue(*item);
    updateUI(*item);
}
#pragma endregion}
void Widget::clearUIPaint()
{
    //清空记录的绘制点数
    this->lineCount = 0;
    //清空曲线
    q_LineSeries->clear();
    v_LineSeries->clear();
    //重新设定坐标轴
    q_Chart->axisX()->setMax(lineCountMax);
    v_Chart->axisX()->setMax(lineCountMax);
    q_Chart->axisX()->setMin(0);
    v_Chart->axisX()->setMin(0);
    //清空日志
    ui->logInfoText->clear();
    //清空日志队列
    logQ.clear();
}
void Widget::updateUI(itemLog itemLog)
{
//    static int count = 0;
    //更新滑块
    if(ui->timeSlider->value() > this->lineCount-5)
        ui->timeSlider->setValue(this->lineCount);

    //图表更新
    if(this->lineCount > lineCountMax)
    {
#pragma region 自动更新,会剔除数据{
//        q_LineSeries->remove(0);
//        q_Chart->axisX()->setMin(this->lineCount-lineCountMax);
//        q_Chart->axisX()->setMax(this->lineCount);
//        v_LineSeries->remove(0);
//        v_Chart->axisX()->setMin(this->lineCount-lineCountMax);
//        v_Chart->axisX()->setMax(this->lineCount);
#pragma endregion}
#pragma region 滑块滑动设置显示范围{
        ui->timeSlider->setEnabled(true);//slider设置开启滑动
        ui->timeSlider->setMaximum(this->lineCount);
        if(ui->timeSlider->value() > this->lineCount-5)
        {
            q_Chart->axisX()->setRange(this->lineCount-lineCountMax,this->lineCount);
            v_Chart->axisX()->setRange(this->lineCount-lineCountMax,this->lineCount);
        }
#pragma endregion}
    }
    else {
        ui->timeSlider->setEnabled(false);//slider设置禁用滑动
    }
    q_LineSeries->append(QPointF(this->lineCount,itemLog.q_res));
    v_LineSeries->append(QPointF(this->lineCount,itemLog.v_res));
    ++this->lineCount;
    //文本框更新
    QString qTxt = QString::number(itemLog.q_res,'f',3) + tr("m<sup>3</sup>");
    QString vTxt = QString::number(itemLog.v_res,'f',3) + tr("x10<sup>-3</sup>m<sup>3</sup>");
    ui->showQText->setText(qTxt);
    ui->showVText->setText(vTxt);

    //铁水状态判断以及控件更新
    QString txtState = "";
    switch (itemLog.state) {
        case 0:txtState = "正常状态";ui->stateText->setStyleSheet("color: rgb(18, 117, 3);");break;
        case 1:txtState = "没有熔体";ui->stateText->setStyleSheet("color: rgb(239, 41, 41);");break;
        case 2:txtState = "异常状态";ui->stateText->setStyleSheet("color: rgb(239, 41, 41);");break;
        default:break;
    }
    ui->stateText->setText(" 当前状态: "+txtState);

    //日至信息更新，保持在最后一行添加，自动滚屏
    QTextCursor cursor = ui->logInfoText->textCursor();
    cursor.movePosition(QTextCursor::End);
    ui->logInfoText->setTextCursor(cursor);
    QChar ch(0x00B3);
    ui->stateText->setText(txtState);//显示铁水状态
    QString str = "时间: " + QString::fromStdString(itemLog.time) + " 当前状态: "+txtState+ "流量: "+QString::number(itemLog.q_res,'f',3)+"m"+ch+" 累积流量: "+QString::number(itemLog.v_res,'f',3)+"x10-3m"+ch+"\n";
    ui->logInfoText->insertPlainText(str);
}
void Widget::recSliderMoved()
{
    if(this->lineCount > lineCountMax)
    {
        int setValue = (ui->timeSlider->value() > lineCountMax) ? ui->timeSlider->value() : lineCountMax;
        q_Chart->axisX()->setRange(setValue-lineCountMax,setValue);
        v_Chart->axisX()->setRange(setValue-lineCountMax,setValue);
    }
    if(dealClass::isDebug == true)
        std::cout<<"slider的值为:"<<ui->timeSlider->value()<<std::endl;
}
Widget::~Widget()
{
    delete ui;
}
void Widget::dealDone()
{
    cam->stop();
    dealV->stop();
//    clearUIPaint();
}
itemLog::itemLog(std::string time,int state,float q_res,float v_res)
{
    this->time = time;
    this->state = state;
    this->q_res = q_res;
    this->v_res = v_res;
}
