#ifndef GUI_H
#define GUI_H

#include <QObject>
#include <QWidget>
#include <QMainWindow>
#include <QToolBar>
#include <QFileDialog>
#include <QPaintDevice>
#include <QDockWidget>


namespace gui {

class OpenDialog : public QFileDialog
{
    Q_OBJECT
public:
    OpenDialog();
};

class MainToolbar : public QToolBar
{
    Q_OBJECT
public:
    MainToolbar();
};

class DrawingArea : public QDockWidget
{
    Q_OBJECT
public:
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow();
};

} // namespace gui

#endif // GUI_H
