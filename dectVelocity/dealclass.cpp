#include "dealclass.h"
#include <QDebug>
#define queue 2
#define fps 25
#define k 0.07758
#define k1 1.099

dealClass::dealClass(int count)
{
    this->stopped = false;
    this->countList = count;//图像处理帧数
    this->vel = 0;
    this->velSum = 0;//初始累积计算结果为0
    this->calTimes = 0;//初始累积计算次数为0
    this->clearDealResFun = true;//初始化清空一下
    this->stateRealTimes = NormalState;//初始状态，正常
    this->timerSigRes = new QTimer(this);//打开相机
    connect(timerSigRes, SIGNAL(timeout()), this, SLOT(recSendRes()));
}
void dealClass::run()
{
    emit sendSignal(true);
    while(!this->stopped)
    {
        if(mutex.tryLock(10))
        {
            if(this->frameL.count() >= countList)
            {
            emit sendSignal(false);
            dealWithV2();
            emit sendSignal(true);
            }
            mutex.unlock();
        }
    }
}
void dealClass::init()
{
    this->stopped = false;
    this->timerSigRes->start(1000);
}
void dealClass::recSendRes()
{
    float resAver = 0;
    if(this->calTimes == 0)
        return;
    resAver = this->velSum / this->calTimes;
    emit sendVel(this->stateRealTimes,resAver);
    this->clearDealResFun = true;
}
void dealClass::dealRes(const int state, float res)
{
    static int normalTimes = 0;
    static int nowaterTimes = 0;
    static int exceptionState = 0;
    if(this->clearDealResFun == true)
    {
        normalTimes = 0;
        nowaterTimes = 0;
        exceptionState = 0;
        this->calTimes = 0;
        this->velSum = 0;
        this->clearDealResFun = false;
    }
    this->calTimes += 1;
    this->velSum += res;
    switch(state)
    {
        case NormalState: normalTimes += 1;break;
        case NoWaterState: nowaterTimes += 1;break;
        case ExceptionState: exceptionState += 1;break;
        default:break;
    }
    if(normalTimes > nowaterTimes && normalTimes > exceptionState)
        this->stateRealTimes = NormalState;
    else if(nowaterTimes > normalTimes && nowaterTimes > exceptionState)
        this->stateRealTimes = NoWaterState;
    else if(exceptionState > normalTimes && exceptionState > nowaterTimes)
        this->stateRealTimes = ExceptionState;
    else {
        this->stateRealTimes = NormalState;
    }
}
//带滤波，消除噪声，方法二
void dealClass::dealWithV2()
{
    static float testRec = 0;
    //图像预处理
    this->isWaterFlow = true;
    Mat front_image = image_deal(this->frameL.at(0));
    Mat back_image;
    if(this->isWaterFlow == true)
    {
        back_image = image_deal(this->frameL.at(1));
    }
    if(this->isWaterFlow == false)
    {
        this->frameL.clear();//清空
        dealRes(NoWaterState,0);//将结果加入计算队列
        return;
    }
    //滤波初始化
    static bool initState = false;
    static double velocity_sum = 0;
    static double velocity_average = 0;
    static double velocity_deal[queue];
    static int j = 0;
    if(initState == false)
    {
        initState = true;
        for (int i = 0;i < queue;i++)
        {
            velocity_deal[i] = 0;
        }
    }
    #pragma region 流速计算{
    //提取图像特征
    double velocity_image = match_feature(front_image, back_image);
    #pragma endregion}
    #pragma region 滤波{
   if (velocity_image > 0)
   {
       velocity_deal[j] = velocity_image;
       velocity_sum = velocity_sum + velocity_deal[j];
       j++;
       if (j == queue )
       {
           double variance = 0;
           velocity_average = velocity_sum / queue;

           for (int i = 0;i < queue;i++)
           {
               variance = variance+ pow((velocity_deal[i] - velocity_average), 2) / queue;
           }
           double sd = pow(variance, 0.5);
           for(int i = 0;i < queue;i++)
           {
               if (velocity_deal[i] > (velocity_average + sd) || velocity_deal[i] < (velocity_average - sd))
               {
                   velocity_deal[i] = 0;
               }
           }
           velocity_sum = 0;
           int aaa = 0;
           for (int i = 0;i < queue;i++)
           {
               if (velocity_deal[i] != 0)
               {
                   velocity_sum = velocity_sum + velocity_deal[i];
                   aaa += 1;
               }
           }
           velocity_average = velocity_sum / aaa;
           velocity_average = k * k1 * velocity_average;
           this->vel  = (float)velocity_average * 10 * 5;
           dealRes(NormalState,this->vel);//将结果加入计算队列
           j = 0;
           velocity_sum = 0;
       }
   }
    #pragma endregion}
    this->frameL.clear();//清空

}
//无滤波，直接获取流速 方法一
void dealClass::dealWithV()
{
    #pragma region 流速计算{
        //图像预处理
        Mat front_image = image_deal(this->frameL.at(0));
        Mat back_image = image_deal(this->frameL.at(1));
        //提取图像特征
        double velocity_image = match_feature(front_image, back_image);
        this->vel = (float)velocity_image;
        this->frameL.clear();//清空
    #pragma endregion}
    dealRes(NoWaterState,this->vel);//将结果加入计算队列
}
Mat dealClass::image_deal(Mat image)//图像预处理
{
    Mat image_roi_gray;
    Mat image_roi,image_des;
    Rect roi;
    roi.x = roiX;//ROI起点x坐标
    roi.y = roiY;//ROI起点y坐标
    roi.width = roiWidth;//ROI宽度
    roi.height = roiHeight;//ROI高度
    image_roi = image(roi);
    cvtColor(image_roi, image_roi_gray, COLOR_BGR2GRAY);//灰度图
//    cvtColor(image, image_gray, COLOR_BGR2GRAY);//灰度图
//    image_roi = image_gray(roi);

    //滤波降噪双边滤波
    cv::bilateralFilter(image_roi_gray,image_des,30,30*2,30/2);
    //image_des = image_roi_gray;
    //imshow("dealWithFrame", image_des);
    //确定是否有水流

    Mat outputmin;
    int outminArray[roiWidth];
    cv::reduce(image_des,outputmin,0,REDUCE_MIN);


    for(int i = 0;i<roiWidth;i++)
    {
        outminArray[i] = outputmin.at<uchar>(0,i);
    }
    int last_aver,now_aver,flag = 1;
//    now_aver = (outminArray[0]+outminArray[1])/2;
    for(int i = 2; i < 20; ++i)
    {
        if(outminArray[i]>threIsWater)
            flag = 0;
    }
    if(flag == 1)
    {
        if(dealClass::isDebug == true)
            std::cout<<"有水流"<<std::endl;
        isWaterFlow = true;
    }
    else {
        if(dealClass::isDebug == true)
            std::cout<<"没有水流"<<std::endl;
        isWaterFlow = false;
    }
    Mat img_Thr;
    if(flag == 1)
    {
        threshold(image_des,img_Thr,0,255,THRESH_BINARY|THRESH_OTSU);

         for(int i = 0; i < roiWidth;  i++)
         {
             for(int j = 0; j<roiHeight; j++)
             {
                 if(image_des.at<uchar>(j,i)>threROI)
                 {
                     image_des.at<uchar>(j,i)=255;
                 }
//                 if(img_Thr.at<uchar>(j,i)==255)
//                 {
//                     image_des.at<uchar>(j,i)=0;
//                 }
//                 else //if(img_Thr.at<uchar>(j,i)==0)
//                 {
//                     image_des.at<uchar>(j,i)=255;
//                 }
             }
         }
         if(dealClass::isDebug == true)
            cv::imshow("img_des",image_des);
        //方法2 不可行
//         int up_flag,down_flag;
//         for(int i = 0; i < 200;  i++)
//         {
//             up_flag = 1;
//             down_flag = 1;
//             for(int j = 0; j<80; j++)
//             {
//                 if(image_des.at<uchar>(j,i)<=60 || image_des.at<uchar>(j,i)==255)
//                 {
//                     up_flag = 0;
//                 }
//                 if(image_des.at<uchar>(79-j,i)<=60 || image_des.at<uchar>(79-j,i)==255)
//                 {
//                     down_flag = 0;
//                 }
//                 if(up_flag == 1 && image_des.at<uchar>(j,i)>60)
//                 {
//                     image_des.at<uchar>(j,i)=255;
//                 }
//                 if(down_flag == 1 && image_des.at<uchar>(79-j,i)>60)
//                 {
//                     image_des.at<uchar>(79-j,i)=255;
//                 }

//             }
//         }
         //imshow("img_thr",image_des);
    }
//     for(int i = 0; i < 200;  i++)
//     {
//         outminArray[i] = 255;
//         for(int j = 0; j<80; j++)
//         {
//             if(outminArray[i]>roi.at<uchar>(j,i))
//             {
//                 outminArray[i] = roi.at<uchar>(j,i);
//             }
//         }
//     }
//     imshow("min",outputmin);

    //
    //draw_Hist(image_roi_gray);

    return image_des;
}
void dealClass::draw_Hist(Mat img_gray)//绘制一维直方图
{
    MatND dstHist;
    int dims = 1;
    float hranges[] = { 0,255 };
    const float* ranges[] = { hranges };
    int size = 256;
    int channels = 0;
    calcHist(&img_gray, 1, &channels, Mat(), dstHist, dims, &size, ranges);

    Mat dstImage(size, size, CV_8U, Scalar(0));
    double minValue = 0;
    double maxValue = 0;
    minMaxLoc(dstHist, &minValue, &maxValue, 0, 0);

    int hpt = saturate_cast<int>(0.9 * size);
    for (int i = 0;i < 256;i++)
    {
        float binValue = dstHist.at<float>(i);
        int realValue = saturate_cast<int>(binValue * hpt / maxValue);
        rectangle(dstImage, Point(i, size - 1), Point((i + 1) - 1, size - realValue), Scalar(255));
    }
    imshow("一维直方图", dstImage);
}
double** dealClass::get_feature(Mat roi)//提取特征
{
    bool flag1 = false, flag2 = false;//判断上升或者下降的flag
     int scale = 5;
     int i;//行数
     int j;//列数
     double temp = 0.001;
     uchar* roi1 = roi.data;
     Mat sum = sum.zeros(roi.rows + 1, roi.cols + 1, CV_32FC1);//78*287
     Mat sqsum = sum.zeros(roi.rows + 1, roi.cols + 1, CV_64FC1);//78*287
     integral(roi, sum, sqsum, CV_32F, CV_64F);
     float* p1 = (float*)sum.data;
     double* p2 = (double*)sqsum.data;
     Mat sum1, sumsq1;
     cv::normalize(sqsum, sumsq1, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
     cv::normalize(sum, sum1, 0, 255, NORM_MINMAX, CV_8UC1, Mat());

     int c = sum.cols;
     int r = sum.rows;
     double* result1 = new double[c];//上边缘的方差
     double* result2 = new double[c];//上边缘的横坐标
     double* result3 = new double[c];//下边缘的方差
     double* result4 = new double[c];//下边缘的横坐标

     double** feature = new double*[c];//feature最多为c行，每行6列

     for (i = 0;i < c;i++)
     {
         feature[i] = new double[6];
     }
     for (i = 0;i < c;i++)
     {
         for (j = 0;j < 5;j++)
         {
             feature[i][j] = 0;
         }
     }

     double* linshi = new double[r];
     for (i = 0;i < r;i++)
     {
         linshi[i] = 0;
     }
     for (j = 0;j < c;j++)
     {
         result1[j] = 0;
         result2[j] = 0;
         result3[j] = 0;
         result4[j] = 0;
     }

     for (j = scale + 1;j < c - scale;j++)
     {

         for (i = scale + 1;i < r - scale;i++)
         {

             double average1 = (*(p1 + (i + scale) * c + j + scale) - *(p1 + (i - scale - 1) * c + j + scale) - *(p1 + (i + scale) * c + j - scale - 1) + *(p1 + (i - scale - 1) * c + j - scale - 1)) / (255 * (2 * scale + 1) * (2 * scale + 1));
             double average2 = (*(p2 + (i + scale) * c + j + scale) - *(p2 + (i - scale - 1) * c + j + scale) - *(p2 + (i + scale) * c + j - scale - 1) + *(p2 + (i - scale - 1) * c + j - scale - 1)) / (255 * 255 * (2 * scale + 1) * (2 * scale + 1));
             double variance = average2 - (average1 * average1);//区域平方的均值减平均值的平方
  //           cout << variance << '\t';
             double a = variance / (variance + 0.0001);
             linshi[i] = a;
 //            cout << linshi[i] << endl;
            /* if (a > result1[j] || a == result1[j])
             {
                 result1[j] = a;
                 result2[j] = i;//寻找下边界

             }*/
         }

         for (i = scale + 1;i < r-scale;i++)//上边界
         {
             if (linshi[i] >= result1[j] )
             {
                 if (linshi[i] > linshi[i - 1] && linshi[i] > linshi[i + 1])
                 {
                     result1[j] = linshi[i];
                     result2[j] = i;
                 }
             }
         }
         for (i = scale + 1;i < r - scale;i++)//下边界
         {
             if (i == result2[j])
             {
                 continue;
             }
             if (linshi[i] >= result3[j])
             {
                 if (linshi[i] > linshi[i - 1] && linshi[i] > linshi[i + 1])
                 {
                     result3[j] = linshi[i];
                     result4[j] = i;
                 }
             }
         }
     }

     for (j = 0;j < c;j++)//整理两条边界
     {
         if (result2[j] >= result4[j])
         {
             int a=0;
             double b=0;
             a = result2[j];
             result2[j] = result4[j];
             result4[j] = a;
             b = result1[j];
             result1[j] = result3[j];
             result3[j] = a;
         }
     }
     /// <summary>
     /// 剔除异常方差（暂时没有效果）
     /// </summary>
     /// <param name="roi"></param>
     /*for (int j = c - scale;j > scale;j--)
     {
         if (result1[j] < 0.9)
         {
             continue;
         }
         if (result1[j] - result1[j - 1] > temp)
         {
             result1[j - 1] = result1[j];
             result2[j - 1] = result2[j];
         }
         else if (result1[j - 1] - result1[j] > temp)
         {
             result1[j] = result1[j - 1];
             result2[j] = result2[j - 1];
         }
         if (result2[j] == result2[j - 2] && !(result2[j] == result2[j - 1]))
         {
             result2[j - 1] = result2[j];
         }
     }*/
     /////////特征提取
     int count = 0;
     for (j = c - scale; j > scale;j--)//j>50??
     {
         if (result2[j] < result2[j - 1])//上升
         {
             flag2 = false;//flag为false为下降，flag为ture为上升
             feature[count][5] = result2[j - 3] - result2[j];
             if (feature[count][5] > 2 && flag1 && count > 0)
             {
                 if ((feature[count][5] == feature[count - 1][2]) && (j - 1 - feature[count - 1][3] < 10))
                 {
                     feature[count - 1][3] = (feature[count - 1][3] + j - 1) / 2;
                     feature[count - 1][4] = (feature[count - 1][4] + feature[count - 1][1]) / 2;

                 }
                 else if ((feature[count][5] == feature[count - 1][2]) && (j - 1 - feature[count - 1][3] >= 10))
                 {
                     feature[count - 1][3] = j - 1;
                     feature[count - 1][4] = result2[j - 1];

                 }
                 if (feature[count][5] > feature[count - 1][2])
                 {
                     feature[count - 1][2] = feature[count][5];
                     feature[count - 1][3] = j - 1;
                     feature[count - 1][4] = result2[j - 1];
                 }
             }
             else if (feature[count][5] > 2 && !flag1)
             {
                 feature[0][0] = count;
                 feature[count][1] = 1;
                 feature[count][2] = feature[count][5];
                 feature[count][3] = j - 1;
                 feature[count][4] = result2[j - 1];//标记编号，上升1或下降2，上升下降幅度，横坐标，纵坐标
                 count++;
                 flag1 = true;
             }
         }
         else if (result2[j] > result2[j - 1])//下降
         {
             flag1 = false;
             feature[count][5] = result2[j] - result2[j - 3];
             if (feature[count][5] > 2 && flag2 && count > 0)
             {
                 if ((feature[count][5] == feature[count - 1][2]) && (j - 1 - feature[count - 1][3] < 10))
                 {
                     feature[count - 1][3] = (feature[count - 1][3] + j - 1) / 2;
                     feature[count - 1][4] = (feature[count - 1][4] + feature[count - 1][1]) / 2;

                 }
                 else if ((feature[count][5] == feature[count - 1][2]) && (j - 1 - feature[count - 1][3] >= 10))
                 {
                     feature[count - 1][3] = j - 1;
                     feature[count - 1][4] = result2[j - 1];

                 }
                 if (feature[count][5] > feature[count - 1][2])
                 {
                     feature[count - 1][2] = feature[count][5];
                     feature[count - 1][3] = j - 1;
                     feature[count - 1][4] = result2[j - 1];
                 }
             }
             else if (feature[count][5] > 2 && !flag2)
             {
                 feature[0][0] = count;
                 feature[count][1] = 2;
                 feature[count][2] = feature[count][5];
                 feature[count][3] = j - 1;
                 feature[count][4] = result2[j - 1];//标记编号，上升1或下降2，上升下降幅度，横坐标，纵坐标
                 count++;
                 flag2 = true;
             }
         }
     }

     /// <summary>
     /// 显示两条边界图像
     /// </summary>
     /// <param name="roi"></param>
     Mat tezheng = tezheng.zeros(r, c, CV_8UC1);
     uchar* p3 = tezheng.data;
     for (j = scale + 1;j < c - scale; j++)
     {
         int row1,row2,col;
         row1 = result2[j];
         row2 = result4[j];
         col = j;
         *(p3 + row1 * c + col) = 255;
         *(p3 + row2 * c + col) = 255;
     }
     if(dealClass::isDebug == true)
        imshow("test",tezheng);

//     cv::circle(tezheng, cv::Point(168, 39), 3, CV_RGB(0, 0, 255), 1);
     //////////////////////////////////////////

     return feature;
}
double dealClass::match_feature(Mat front_image,Mat back_image)//特征匹配
{
    int count = 0;double displacement = 0;
    double result;
    double** front_feature, **back_feature;
    front_feature = get_feature(front_image);
    back_feature = get_feature(back_image);
    double* array = new double[((int(front_feature[0][0])+1)*(int(back_feature[0][0])+1))];
    for (int i = 0;i < (front_feature[0][0] + 1) * (back_feature[0][0] + 1);i++)
    {
        array[i] = 0;
    }
    for (int i = 0;i <front_feature[0][0]+1 ;i++)
    {
        for (int j = 0;j < back_feature[0][0]+1;j++)
        {
            if ((front_feature[i][1] == back_feature[j][1]) &&
                    (back_feature[j][3] - front_feature[i][3] < 30) &&
                    (back_feature[j][3] - front_feature[i][3] > 3) &&
                    (back_feature[j][2] - front_feature[i][2] < 3) &&
                    (front_feature[i][2] - back_feature[j][2] < 3))
            {
                *(array + i * int(back_feature[0][0] + 1) + j) = back_feature[j][3] - front_feature[i][3];
                count++;
            }
        }
    }
    for (int i = 0;i < (front_feature[0][0] + 1) * (back_feature[0][0] + 1);i++)
    {
        displacement = displacement + array[i];
    }
    delete[] array;//释放动态分配的内存空间
    if (count > 0)
    {
        return displacement / count;
    }
    else return 0;
}
double dealClass::GetFunction(Mat roi)
{
    bool flag1 = false, flag2 = false;//判断上升或者下降的flag
    int scale = 5;
    int i;//行数
    int j;//列数
    double temp = 0.001;
    uchar* roi1 = roi.data;
    Mat sum = sum.zeros(roi.rows + 1, roi.cols + 1, CV_32FC1);//78*287
    Mat sqsum = sum.zeros(roi.rows + 1, roi.cols + 1, CV_64FC1);//78*287
    integral(roi, sum, sqsum, CV_32F, CV_64F);
    float* p1 = (float*)sum.data;
    double* p2 = (double*)sqsum.data;
    Mat sum1, sumsq1;
    cv::normalize(sqsum, sumsq1, 0, 255, NORM_MINMAX, CV_8UC1, Mat());
    cv::normalize(sum, sum1, 0, 255, NORM_MINMAX, CV_8UC1, Mat());

    int c = sum.cols;
    int r = sum.rows;
    double* result1 = new double[c];//上边缘的方差
    double* result2 = new double[c];//上边缘的横坐标
    double* result3 = new double[c];//下边缘的方差
    double* result4 = new double[c];//下边缘的横坐标
    double* x_label = new double[c];//下边缘的横坐标
    double* y_label = new double[c];//下边缘的横坐标s
    double** feature = new double* [c];//feature最多为c行，每行6列

#pragma region getedge 上边界result2[c] 下边界result4[c] 中间y_label[c]
    for (i = 0;i < c;i++)
    {
        feature[i] = new double[6];
    }
    for (i = 0;i < c;i++)
    {
        for (j = 0;j < 5;j++)
        {
            feature[i][j] = 0;
        }
    }

    double* linshi = new double[r];
    for (i = 0;i < r;i++)
    {
        linshi[i] = 0;
    }
    for (j = 0;j < c;j++)
    {
        result1[j] = 0;
        result2[j] = 0;
        result3[j] = 0;
        result4[j] = 0;
    }

    for (j = scale + 1;j < c - scale;j++)
    {

        for (i = scale + 1;i < r - scale;i++)
        {

            double average1 = (*(p1 + (i + scale) * c + j + scale) - *(p1 + (i - scale - 1) * c + j + scale) - *(p1 + (i + scale) * c + j - scale - 1) + *(p1 + (i - scale - 1) * c + j - scale - 1)) / (255 * (2 * scale + 1) * (2 * scale + 1));
            double average2 = (*(p2 + (i + scale) * c + j + scale) - *(p2 + (i - scale - 1) * c + j + scale) - *(p2 + (i + scale) * c + j - scale - 1) + *(p2 + (i - scale - 1) * c + j - scale - 1)) / (255 * 255 * (2 * scale + 1) * (2 * scale + 1));
            double variance = average2 - (average1 * average1);//区域平方的均值减平均值的平方
            double a = variance / (variance + 0.0001);
            linshi[i] = a;
        }

        for (i = scale + 1;i < r - scale;i++)//上边界
        {
            if (linshi[i] >= result1[j])
            {
                if (linshi[i] > linshi[i - 1] && linshi[i] > linshi[i + 1])
                {
                    result1[j] = linshi[i];
                    result2[j] = i;
                }
            }
        }
        for (i = scale + 1;i < r - scale;i++)//下边界
        {
            if (i == result2[j])
            {
                continue;
            }
            if (linshi[i] >= result3[j])
            {
                if (linshi[i] > linshi[i - 1] && linshi[i] > linshi[i + 1])
                {
                    result3[j] = linshi[i];
                    result4[j] = i;
                }
            }
        }
    }
    for (j = 0;j < c;j++)//整理两条边界
    {
        if (result2[j] >= result4[j])
        {
            int a = 0;
            double b = 0;
            a = result2[j];
            result2[j] = result4[j];
            result4[j] = a;
            b = result1[j];
            result1[j] = result3[j];
            result3[j] = a;
        }
    }
    for (j = 0;j < c;j++)
    {
        x_label[j] = j;
        y_label[j] = (result2[j] + result4[j]) / 2;
    }
    Mat tezheng = tezheng.zeros(r, c, CV_8UC1);
    uchar* p3 = tezheng.data;
    for (j = scale + 1;j < c - scale; j++)
    {
        int row1, row2, col;
        int row3;
        row1 = result2[j];
        row2 = result4[j];
        row3 = y_label[j];
        col = j;
        *(p3 + row1 * c + col) = 255;
    }
    if(dealClass::isDebug == true)
        imshow("边界", tezheng);


#pragma endregion
        double y_max=0, y_min = roi.cols;
        double x_max = c - scale, x_min = scale + 1;
        const int var_long = 7;
        int m = 0;
        double var[var_long] = { 0,0,0,0,0 },var_ave = 0,var_sum = 0,var1=0;
        double var_sum1 = 0;
        for (j = scale + 1;j < c - scale - var_long;j++)
        {
            for (m = 0;m < var_long;m++)
            {
                var[m] = y_label[j+m];
                var_sum += var[m];
            }
            var_ave = var_sum / var_long;
            for (m = 0;m < var_long;m++)
            {
                var_sum1 = var_sum1 + pow((var[m] - var_ave), 2);
            }
            var1 = var_sum1 / var_long;
            if(dealClass::isDebug == true)
                std::cout<<var1<<'\t';
            if (var1 >= 40)
            {
                x_max = j;
                break;
            }

            var_sum = 0;
            var_sum1 = 0;
        }

        for (i = 0;i < r; i++)
        {
            int col = x_max;
            *(p3 + i * c + col) = 255;
        }
        if(dealClass::isDebug == true)
            imshow("边界", tezheng);
        for (j = x_min;j < x_max;j++)
        {
            if (y_label[j] >= y_max)
            {
                y_max = y_label[j];
            }
            if (y_label[j] <= y_min)
            {
                y_min = y_label[j];
            }
        }
        double tan = 0;
        static double tan_sum = 0;
        double tan_ave;
        static int count1 = 1;
        tan = (y_max - y_min) / (x_max - x_min) ;
        tan_sum = (tan_sum + tan);
        tan_ave = double(tan_sum/count1 );
        vel = std::sqrt(1/tan);


    return vel;

}
void dealClass:: recFrame(Mat frame1,Mat frame2)
{
    mutex.lock();
    this->frameL.append(frame1);
    this->frameL.append(frame2);
    if(dealClass::isDebug == true)
    {
        QString str = QString::number(this->frameL.count());
        qDebug()<<str;
    }
    mutex.unlock();
}
void dealClass::stop()
{
    this->stopped = true;
    this->timerSigRes->stop();//停止定时器
}
dealClass::~dealClass()
{
    this->stop();
}
