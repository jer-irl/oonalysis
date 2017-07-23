#include <QObject>
#include <QFileDialog>
#include <QToolBar>
#include <QAction>

#include <QDebug>

#include "gui.h"
#include "Ctx.h"

namespace gui {

MainToolbar::MainToolbar() : QToolBar()
{
    // Open selection
    QAction* act = this->addAction("Open");
    QObject::connect(
            act,
            &QAction::triggered,
            oonalysis::Ctx::CTX()->Controller,
            &oonalysis::GuiController::handle_open_dialog_request);
    return;
}

} // namespace oonalysis
