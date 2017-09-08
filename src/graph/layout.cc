#include "layout.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::graph {

void force_directed(Field& field) {
    LOG(INFO, "Making force-directed layout");

    field.relax_all(100);

    return;
}

} // namespace oonalysis::graph
