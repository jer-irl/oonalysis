#include "layout.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::graph {

void force_directed(Field field) {
    LOG(INFO, "Making force-directed layout");

    for (int i = 0; i < 100; i++) {
        field.relax();
    }

    return;
}

} // namespace oonalysis::graph
