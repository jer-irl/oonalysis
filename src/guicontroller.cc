#include <QtDebug>
#include <QList>
#include <QFileDialog>
#include <QUrl>
#include "Ctx.h"
#include "guicontroller.h"
#include "gui.h"

namespace oonalysis {

void GuiController::handle_open_dialog_request()
{
    qDebug() << "Handling open request";

    gui::OpenDialog* dialog = new gui::OpenDialog();
    dialog->exec();
    delete dialog;
    return;
}

void GuiController::handle_open_selection(QList<QUrl> urls)
{
    qDebug() << "Handling open selection";

    Ctx::CTX()->add_files_from_selection(urls);
    return;
}

} // namespace oonalysis
