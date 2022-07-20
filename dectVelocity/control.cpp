#include "control.h"
#pragma region gpio构造函数{
controlGPIO::controlGPIO(int GpioPin)
{
    this->GpioPin = GpioPin;
    init(this->GpioPin);//初始化gpio

}
#pragma endregion}
#pragma region gpio初始化{
void controlGPIO::init(int gpiopin)
{
    FILE *pfile = NULL;
    pfile = fopen("/sys/class/gpio/export","w");//写模式
    fprintf(pfile,"%d",gpiopin);
    fclose(pfile);
    string str = "/sys/class/gpio/gpio" + to_string(gpiopin) + "/direction";
    pfile = fopen(str.c_str(),"w");
    fprintf(pfile,"out");
    fclose(pfile);
}
#pragma endregion}
#pragma region 设置高电平{
void controlGPIO::setHigh()
{
    FILE *pfile = NULL;
    string str = "/sys/class/gpio/gpio" + to_string(this->GpioPin) + "/value";
    pfile = fopen(str.c_str(),"w");
    fprintf(pfile,"%d",1);
    fclose(pfile);
}
#pragma endregion}
#pragma region 设置低电平{
void controlGPIO::setLow()
{
    FILE *pfile = NULL;
    string str = "/sys/class/gpio/gpio" + to_string(this->GpioPin) + "/value";
    pfile = fopen(str.c_str(),"w");
    fprintf(pfile,"%d",0);
    fclose(pfile);
}
#pragma endregion}
#pragma region pwm构造函数{
controlPWM::controlPWM(int chip,float rate)
{
    this->pwm_chip = chip;
    this->pwmRate = rate;
    this->pwm_period = 20000;
    this->pwm_duty = this->pwm_period * this->pwmRate;
    initExport(this->pwm_chip);
    pwmDisable(this->pwm_chip);
    pwmConfig(this->pwm_chip);
    pwm_polarity();
    pwmEnable(this->pwm_chip);
}
#pragma endregion}
#pragma region 获取控制权{
void controlPWM::initExport(int chip)
{
    FILE *pfile = NULL;
    string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/export";
    pfile = fopen(str.c_str(), "w");
    fprintf(pfile,"%d",0);
    fclose(pfile);
}
#pragma endregion}
#pragma region 放弃(移交)控制权{
void controlPWM::unExport(int chip)
{
    FILE *pfile = NULL;
    string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/export";
    pfile = fopen(str.c_str(), "w");
    fprintf(pfile,"%d",1);
    fclose(pfile);
}
#pragma endregion}
#pragma region 打开pwm{
void controlPWM::pwmEnable(int chip)
{
    FILE *pfile = NULL;
    string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/pwm0/enable";
    pfile = fopen(str.c_str(), "w");
    fprintf(pfile,"%d",1);
    fclose(pfile);
}
#pragma endregion}
#pragma region 关闭pwm{
void controlPWM::pwmDisable(int chip)
{
    FILE *pfile = NULL;
    string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/pwm0/enable";
    pfile = fopen(str.c_str(), "w");
    fprintf(pfile,"%d",0);
    fclose(pfile);
}
#pragma endregion}
#pragma region 设置占空比{
void controlPWM::pwmConfig(int chip)
{
    FILE *pfile = NULL;
    {
        string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/pwm0/period";
        pfile = fopen(str.c_str(),"w");
        fprintf(pfile,"%d",this->pwm_period);
        fclose(pfile);
    }
    {
        string str = "/sys/class/pwm/pwmchip" + to_string(chip)+"/pwm0/duty_cycle";
        pfile = fopen(str.c_str(),"w");
        fprintf(pfile,"%d",this->pwm_duty);
        fclose(pfile);
    }
}
#pragma endregion}
#pragma region 设置极性{
//决定了高占空比的信号是输出高电平，决定了低占空比的信号是输出低电平
void controlPWM::pwm_polarity()
{
    FILE *pfile = NULL;
    string str = "/sys/class/pwm/pwmchip" + to_string(this->pwm_chip)+"/pwm0/polarity";
    pfile = fopen(str.c_str(), "w");
    fprintf(pfile,"%s","normal");
    fclose(pfile);
}
#pragma endregion}
#pragma region 用户调节占空比{
void controlPWM::set_duty(float rate)
{
    this->pwmRate = rate;
    this->pwm_duty = this->pwm_period * this->pwmRate;
    pwmDisable(this->pwm_chip);
    pwmConfig(this->pwm_chip);
    pwmEnable(this->pwm_chip);
}
#pragma endregion}








