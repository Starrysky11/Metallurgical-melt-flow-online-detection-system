#ifndef SLIDERCLICK_H
#define SLIDERCLICK_H
#include <QSlider>

class SliderClick : public QSlider
{
public:
    SliderClick(QWidget *parent = 0);
protected:
    void mousePressEvent(QMouseEvent *ev);
};

#endif // SLIDERCLICK_H
