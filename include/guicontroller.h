#ifndef GUICONTROLLER_H
#define GUICONTROLLER_H

#include <QObject>
#include <QList>
#include <QUrl>


namespace oonalysis {

class GuiController : public QObject {
    Q_OBJECT
public slots:
    void handle_open_dialog_request();
    void handle_open_selection(QList<QUrl> urls);

}; // class GuiController

} // namespace oonalysis

#endif // GUICONTROLLER_H
