#include "cells.h"


void Subject::attachObserver(Observer *observer)
{
    cells.push_back(observer);
}

void Subject::detachObserver(Observer *observer)
{
    cells.remove(observer);
}

bool Subject::getStatus()
{
    return done;
}

void Subject::notify() {
    for (auto const& cell : cells)
    {
        cell->update();
    }
    qDebug()<<"notified";
}
