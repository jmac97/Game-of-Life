#include "slider.h"

Slider::Slider() {
    this->setValue(50);
    this->setTickPosition((QSlider::TickPosition(1)));
    this->setOrientation(Qt::Horizontal);
}

void Slider::set_parameters(int tick_interval, int range_min, int range_max, int single_step)
{
    this->setTickInterval(tick_interval);
    this->setRange(range_min, range_max);
    this->setSingleStep(single_step);
    this->setValue((range_max - range_min)/2);
}
