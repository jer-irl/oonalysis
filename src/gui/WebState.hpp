#ifndef GUI_WEBSTATE_HPP
#define GUI_WEBSTATE_HPP

#include <QObject>

namespace oonalysis::gui {

class WebState : public QObject {
Q_OBJECT

public:
    using QObject::QObject;

    QString testField = "Hello";

public slots:
    void doExit() { exit(0); }
};

} // oonalysis::gui

#endif // GUI_WEBSTATE_HPP