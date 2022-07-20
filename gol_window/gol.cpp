#include "gol.h"

gol::gol(QWidget *parent) : QWidget{parent} {
  cells_current.resize(QWidget::width() + grid_offset,
                       std::vector<bool>(QWidget::height() + grid_offset));
  cells_next_gen.resize(QWidget::width() + grid_offset,
                        std::vector<bool>(QWidget::height() + grid_offset));

  this->set_timer();
}

// After x msec, gol widget gets updated and MainWindow changes
// Start(x) begins timer where x is in the above interval in msec
void gol::set_timer() {
  if (timer_started == false) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, QOverload<>::of(&gol::update));
    timer->start(250);
    timer_started = true;
  }
}

// When signal from horizontal slider is received, timer interval
// gets updated based on slider value
void gol::speed_changed(int value)
{
    // Range of slider is 1-100. I want the speed to increase
    // when you drag the slider to the right, so I need to
    // reverse the values I receive
    int v = 100 - value;

    // *10 since slider is 1-100 and I want slowest interval to be
    // 1 second or 1000 msec
    timer->setInterval(v * 10);
}

// "Starter" patterns for testing. Place in mousePressEvent
void gol::block() {
  if (cells_current[0 + scale][0 + scale] != alive) {
    cells_current[0 + scale][0 + scale] = alive;
    cells_current[11 + scale][0 + scale] = alive;
    cells_current[0 + scale][10 + scale] = alive;
    cells_current[10 + scale][10 + scale] = alive;
    this->update();
  }
}

void gol::blinker() {
  if (cells_current[0 + scale][0 + scale] != alive) {
    cells_current[0 + scale][0 + scale] = alive;
    cells_current[0 + scale][10 + scale] = alive;
    cells_current[0 + scale][20 + scale] = alive;
    this->update();
  }
}

void gol::toad() {
  if (cells_current[30 + scale][30 + scale] != alive) {
    cells_current[30 + scale][30 + scale] = alive;
    cells_current[50 + scale][20 + scale] = alive;
    cells_current[60 + scale][30 + scale] = alive;
    cells_current[30 + scale][40 + scale] = alive;
    cells_current[60 + scale][40 + scale] = alive;
    cells_current[40 + scale][50 + scale] = alive;
    this->update();
  }
}

void gol::beacon() {
  if (cells_current[30 + scale][30 + scale] != alive) {
    cells_current[30 + scale][30 + scale] = alive;
    cells_current[40 + scale][30 + scale] = alive;
    cells_current[30 + scale][40 + scale] = alive;
    cells_current[60 + scale][50 + scale] = alive;
    cells_current[50 + scale][60 + scale] = alive;
    cells_current[60 + scale][60 + scale] = alive;
    this->update();
  }
}

void gol::glider() {
  if (cells_current[30 + scale][30 + scale] != alive) {
    cells_current[30 + scale][30 + scale] = alive;
    cells_current[50 + scale][30 + scale] = alive;
    cells_current[40 + scale][40 + scale] = alive;
    cells_current[50 + scale][40 + scale] = alive;
    cells_current[40 + scale][50 + scale] = alive;
    this->update();
  }
}

// Whenever use clicks on a square at start of the program, x and y get stored
// in cells_current Calls update() at the end
void gol::mousePressEvent(QMouseEvent *event) {
  if (generation == 0 && !play) {
    // "Starter" pattern
    glider();

    userX = event->x();
    userY = event->y();

    // Truncating the X and Y values to be multiples of 10 to fit the grid
    // Eg 51-59 become 50
    userX = (userX / spacing) * spacing;
    userY = (userY / spacing) * spacing;

    qDebug() << "(" << userX << ", " << userY << ")";


    if (cells_current[userX + scale][userY + scale] == alive) {
      cells_current[userX + scale][userY + scale] = !alive;
    } else {
      cells_current[userX + scale][userY + scale] = alive;
    }

    this->update();
  }
}

// Goes through the current grid (cells_current), compares each cell to its
// neighbor, then fills cells_next_gen based on GOL rules
void gol::get_next_generation() {
  int alive_neighbors = 0;

  // Technically grid starts at 10. Need off set to handle checking cells on the
  // edge of the grid
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
        alive_neighbors -= 1; // Remove the alive neighbors count that includes
                              // the the current cell
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

// After filling the grid with cells_next_gen, fill cells_current with the
// current grid of cells by grabbign the values still stored in cells_next_gen.
// Latter is filled with dead cells
void gol::cell_swap() {
  for (int x = 0; x < cells_current.size(); x += spacing) {
    for (int y = 0; y < cells_current[x].size(); y += spacing) {
      cells_current[x][y] = cells_next_gen[x][y];
      cells_next_gen[x][y] = !alive;
    }
  }
}

// Sets both cell vectors back to zero
void gol::reset_GOL() {
  for (int x = 0; x < cells_current.size(); x += spacing) {
    for (int y = 0; y < cells_current[x].size(); y += spacing) {
      cells_current[x][y] = !alive;
      cells_next_gen[x][y] = !alive;
    }
  }
  generation = 0;
}

void gol::debug()
{
    qDebug() << "saw signal, triggering slot";
}

void gol::play_GOL() { play = true; }

void gol::pause_GOL() { play = false; }

// Draws the grid and the cells
void gol::paintEvent(QPaintEvent *event) {

  QPainter painter(this);

  painter.setBrush(Qt::white);
  painter.drawRect(0, 0, QWidget::width(), QWidget::height());

  painter.setBrush(Qt::black);

  // Drawing x lines of the grid
  for (int x = 0; x <= QWidget::width(); x += spacing) {
    painter.drawLine(x, 0, x, QWidget::height());
  }

  // Drawing y lines of the grid
  for (int y = 0; y <= QWidget::height(); y += spacing) {
    painter.drawLine(0, y, QWidget::width(), y);
  }

  // If the play button has been pressed...
  if (play) {
    qDebug() << "Generation: " << generation;

    get_next_generation();

    for (int x = scale; x < cells_next_gen.size() - spacing; x += spacing) {
      for (int y = scale; y < cells_next_gen.size() - spacing; y += spacing) {
        if (cells_next_gen[x][y] == alive) {
          painter.drawRect(x - scale, y - scale, spacing, spacing);
        }
      }
    }

    cell_swap();
    generation++;

  } else if (!play) {
    if (generation == 0) {
      glider();
    }

    for (int x = scale; x < cells_current.size() - spacing; x += spacing) {
      for (int y = scale; y < cells_current[x].size() - spacing; y += spacing) {
        if (cells_current[x][y] == alive) {
          painter.drawRect(x - scale, y - scale, spacing, spacing);
        }
      }
    }
  }
}
