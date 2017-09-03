#include "ctx.h"

namespace oonalysis::gui {

Ctx* Ctx::inst() {
    static Ctx ctx{ };
    return &ctx;
}

Ctx::Ctx() :
        mw(400, 400, "oonalysis") {
}

void Ctx::show() {
    mw.show();
}

} // oonalysis::gui

