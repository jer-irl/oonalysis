#include "field.h"

namespace oonalysis::graph {

void Field::relax_all(int times) {
    for (int i = 0; i < times; i++) {
        relax_all();
    }
}

} // namespace oonalysis::graph
