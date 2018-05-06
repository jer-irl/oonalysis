#ifndef GUI_WEBSTATE_HPP
#define GUI_WEBSTATE_HPP

#include <QObject>

namespace oonalysis::gui {

class WebInterface : public QObject {
Q_OBJECT

public:
    WebInterface(QObject* parent = nullptr) : QObject(parent) { }

    QString testField = "Hello";

public slots:
    void requestInclusions();

};

} // oonalysis::gui

#endif // GUI_WEBSTATE_HPP