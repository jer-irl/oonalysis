#include <string>
#include <vector>

#include "Ctx.h"
#include "OOProg.h"
#include "oonalysis.h"

namespace oonalysis::core {

Ctx* Ctx::CTX() {
    static Ctx* CTX = new Ctx();
    return CTX;
}

Ctx::Ctx() {
}

OOProg gen_program();

} // namespace oonalysis::core
