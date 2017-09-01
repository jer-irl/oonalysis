#include "ctx.h"

namespace oonalysis::gui {

Ctx* Ctx::inst() {
    static Ctx ctx{ };
    return &ctx;
}

} // oonalysis::gui

