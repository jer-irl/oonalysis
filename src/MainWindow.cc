#include <QObject>
#include "gui.h"

namespace gui {

MainWindow::MainWindow() : QMainWindow()
{
    MainToolbar* main_toolbar = new MainToolbar();
    this->addToolBar(main_toolbar);

    DrawingArea* drawing_area = new DrawingArea();
    this->addDockWidget(Qt::AllDockWidgetAreas, drawing_area);
}


}
