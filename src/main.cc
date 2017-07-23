#include <QtGlobal>
#include <QApplication>
#include <QDebug>
#include "gui.h"
#include "oonalysis.h"
#include "Ctx.h"

void start_app(int argc, char** argv)
{
    QApplication app(argc, argv);
    gui::MainWindow win;
    win.show();
    app.exec();
    return;
}

void config_log()
{
    qSetMessagePattern("[%{type}] %{appname} (%{file}:%{line}) - %{message}");
    return;
}

int main(int argc, char** argv)
{
    config_log();
    qInfo() << "Starting oonalysis";

    start_app(argc, argv);

    return 0;
}
