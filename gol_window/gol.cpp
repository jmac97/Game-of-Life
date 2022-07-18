#include "gol.h"

gol::gol(QWidget *parent) : QWidget{parent} {
  this->seed_grid();
  this->set_timer();
}

void gol::set_timer() {
  if (timer_started == false) {
    QTimer *timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&gol::update));
    timer->start(1000);
    timer_started = true;
  }
}

// void gol::set_window_parameters(int w, int h) {
//     window_width = w;
//     window_height = h;
//     setFixedSize(window_width, window_height);
// }

void gol::set_generation(int gen) { generation = gen; }

void gol::seed_grid() {

  cells_current.resize(QWidget::width() + grid_offset,
                       std::vector<bool>(QWidget::height() + grid_offset));
  cells_next_gen.resize(QWidget::width() + grid_offset,
                        std::vector<bool>(QWidget::height() + grid_offset));

  for (auto x = cells_current.begin(); x != cells_current.end(); x++) {

    for (auto y = x->begin(); y != x->end(); y++) {
      *y = !alive;
      *y = !alive;
    }
  }

  //    block();
//  blinker();
  glider();
}

 void gol::block(){
     cells_current[0 + scale][0 + scale] = alive;
     cells_current[11 + scale][0 + scale] = alive;
     cells_current[0 + scale][10 + scale] = alive;
     cells_current[10 + scale][10 + scale] = alive;
 }

void gol::blinker() {
  cells_current[0 + scale][0 + scale] = alive;
  cells_current[0 + scale][10 + scale] = alive;
  cells_current[0 + scale][20 + scale] = alive;
}

 void gol::toad() {
     cells_current[30 + scale][30 + scale] = alive;
     cells_current[50 + scale][20 + scale] = alive;
     cells_current[60 + scale][30 + scale] = alive;
     cells_current[30 + scale][40 + scale] = alive;
     cells_current[60 + scale][40 + scale] = alive;
     cells_current[40 + scale][50 + scale] = alive;
 }

 void gol::beacon() {
     cells_current[30 + scale][30 + scale] = alive;
     cells_current[40 + scale][30 + scale] = alive;
     cells_current[30 + scale][40 + scale] = alive;
     cells_current[60 + scale][50 + scale] = alive;
     cells_current[50 + scale][60 + scale] = alive;
     cells_current[60 + scale][60 + scale] = alive;
 }

 void gol::glider() {
     bool alive = true;
     cells_current[30 + scale][30 + scale] = alive;
     cells_current[50 + scale][30 + scale] = alive;
     cells_current[40 + scale][40 + scale] = alive;
     cells_current[50 + scale][40 + scale] = alive;
     cells_current[40 + scale][50 + scale] = alive;
 }

void gol::get_next_generation() {
  int alive_neighbors = 0;

  for (int x = spacing; x < cells_current.size() - spacing; x += spacing) {
    for (int y = spacing; y < cells_current[x].size() - spacing; y += spacing) {

      for (int neighborX = x - spacing; neighborX <= x + spacing;
           neighborX += spacing) {
        for (int neighborY = y - spacing; neighborY <= y + spacing;
             neighborY += spacing) {

          if (cells_current[neighborX][neighborY] == alive) {
            alive_neighbors++;
          }
        }
      }

      if (cells_current[x][y] == alive) {
        alive_neighbors -= 1; // remove the alive neighbors count that includes
                              // the current cell
        if (alive_neighbors == 2 || alive_neighbors == 3) {
          cells_next_gen[x][y] = alive;
        } else {
          cells_next_gen[x][y] = !alive;
        }
      } else {
        if (alive_neighbors == 3) {
          cells_next_gen[x][y] = alive;
        } else {
          cells_next_gen[x][y] = !alive;
        }
      }

      alive_neighbors = 0;
    }
  }
}

void gol::cell_swap() {
  for (int x = 0; x < cells_current.size(); x += spacing) {
    for (int y = 0; y < cells_current[x].size(); y += spacing) {
      cells_current[x][y] = cells_next_gen[x][y];
      cells_next_gen[x][y] = !alive;
    }
  }
}

void gol::playGOL() { play = true; }

void gol::pauseGOL() { play = false; }

void gol::paintEvent(QPaintEvent *event) {

  QPainter painter(this);

  for (int x = 0; x <= QWidget::width(); x += spacing) {
    painter.drawLine(x, 0, x, QWidget::height());
  }

  for (int y = 0; y <= QWidget::height(); y += spacing) {
    painter.drawLine(0, y, QWidget::width(), y);
  }

  painter.setBrush(Qt::cyan);
  ////    painter.setPen(Qt::cyan);
  if (play) {
    qDebug() << "Generation: " << generation;
    if (generation == 0) {
      for (int x = scale; x < cells_current.size() - spacing; x += spacing) {
        for (int y = scale; y < cells_current[x].size() - spacing;
             y += spacing) {
          if (cells_current[x][y] == alive) {
            qDebug() << "alive";
            painter.drawRect(x - scale, y - scale, spacing, spacing);
          }
        }
      }
    } else {
      get_next_generation();
      for (int x = scale; x < cells_next_gen.size() - spacing; x += spacing) {
        for (int y = scale; y < cells_next_gen.size() - spacing; y += spacing) {
          if (cells_next_gen[x][y] == alive) {
            painter.drawRect(x - scale, y - scale, spacing, spacing);
          }
        }
      }
      cell_swap();
    }
    generation++;
  } else if (!play && generation != 0) {
    qDebug() << "paused";
    for (int x = scale; x < cells_current.size() - spacing; x += spacing) {
      for (int y = scale; y < cells_current[x].size() - spacing; y += spacing) {
        if (cells_current[x][y] == alive) {
          qDebug() << "alive";
          painter.drawRect(x - scale, y - scale, spacing, spacing);
        }
      }
    }
  }
}
