#ifndef CONTROL_H
#define CONTROL_H
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <fcntl.h>
using namespace std;
class controlGPIO
{
private:
//    const static int GpioPin = 39;
    int GpioPin;
public:
    controlGPIO(int);
    void init(int);//初始化GPIO
    void setHigh();//置高
    void setLow();//置低
};
class controlPWM
{
private:
    int pwm_chip;
    int pwm_period;
    int pwm_duty;
    float pwmRate;
    void initExport(int);
    void unExport(int);
    void pwmEnable(int);
    void pwmDisable(int);
    void pwmConfig(int);
    void pwm_polarity();
public:
    controlPWM(int,float rate=0);
    void set_duty(float);
};
#endif // CONTROL_H
