#include <FL/Fl.H>
#include "gui/ctx.h"

int main(void) {
    oonalysis::gui::Ctx* ctx = oonalysis::gui::Ctx::inst();
    ctx->show();
    return Fl::run();
}
