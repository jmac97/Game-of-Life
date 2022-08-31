#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>

class Slider : public QSlider
{
    Q_OBJECT

public:
    Slider();
    void set_parameters(int tick_interval, int range_min, int range_max, int single_step);

signals:

};

#endif // SLIDER_H
