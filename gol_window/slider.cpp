#include "slider.h"

Slider::Slider() {
    // This will be adjustable in the future
    this->setTickInterval(10);
    this->setRange(1, 100);
    this->setValue(50);
    this->setSingleStep(10);
    this->setTickPosition((QSlider::TickPosition(1)));
    this->setOrientation(Qt::Horizontal);
}

