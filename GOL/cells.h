#ifndef CELLS_H
#define CELLS_H

#include <list>


class Observer {
public:
    void update();
};

class Subject {
  std::list<class Observer *> cells;
  bool done = false;

public:
  void attachObserver(Observer *observer)
  {
      cells.push_back(observer);
  }

  void detachObserver(Observer *observer)
  {
      cells.remove(observer);
  }

  bool getStatus()
  {
      return done;
  }

  void notify() {
      for (auto const& cell : cells)
      {
          cell->update();
      }
  }
};


class Cell : public Observer {
public:
private:
  int xPosition;
  int yPosition;
  bool alive = true;
};

#endif // CELLS_H
