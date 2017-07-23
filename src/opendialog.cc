#include <QFileDialog>
#include "gui.h"
#include "Ctx.h"
#include "guicontroller.h"

namespace gui {

OpenDialog::OpenDialog() : QFileDialog()
{
    this->setViewMode(QFileDialog::Detail);
    this->setOptions(QFileDialog::ReadOnly | QFileDialog::DontUseCustomDirectoryIcons);
    this->setAcceptMode(QFileDialog::AcceptOpen);
    QObject::connect(
            this,
            &QFileDialog::urlsSelected,
            oonalysis::Ctx::CTX()->Controller,
            &oonalysis::GuiController::handle_open_selection);
    return;
}

}; // namespace gui
