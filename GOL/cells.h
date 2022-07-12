#ifndef CELLS_H
#define CELLS_H

#include <list>
#include <tuple>
#include <QDebug>

class Subject {
  std::list<class Observer *> cells;
  bool done = false;
  int x = 20;
  int y = 30;

public:
  void attachObserver(Observer *observer);
  void detachObserver(Observer *observer);
  bool getStatus();
  std::tuple<int, int> getCoordinates() {
      return {x, y};
  }
  void notify();
};

class Observer {
    Subject *subject;

public:
    Observer(Subject *sub, int _x, int _y) {
        subject = sub;
        x = _x;
        y = _y;
        neighborCount = 0;
        subject->attachObserver(this);
    }
    virtual void update() = 0;
protected:
    Subject *getSubject() {
        return subject;
    }

    std::tuple<int, int> sendCoordinates() {
        return {x, y};
    }
    int x;
    int y;
    int neighborCount;

private:
    bool alive = true;
};

class Cell : public Observer {
public:
    Cell(Subject *sub, int _x, int _y) : Observer(sub, _x, _y) {}
    void update() {
        std::tuple<int, int> coordinates;
        coordinates = getSubject()->getCoordinates();

        int subX = std::get<0>(coordinates);
        int subY = std::get<1>(coordinates);

        if ((subX >= (x-10)) && (subX <= (x+20))) {
            if ((subY >= (y-10)) && (subY<= (y+20))) {
                qDebug() << "this is a neighbor";
            } else {
                qDebug() << "this isn't a neighbor becasuse of Y";
            }
        } else {
            qDebug() << "this isn't a neighbor because of X";
        }
    }
};

#endif // CELLS_H
