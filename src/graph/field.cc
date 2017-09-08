#include "force.h"
#include "field.h"

namespace oonalysis::graph {


Field::Field(float xsize, float ysize, float zsize, std::vector<std::shared_ptr<Node>> nodes) {
    this->xsize = xsize;
    this->ysize = ysize;
    this->zsize = zsize;
    this->nodes = nodes;
}

void Field::relax_all(int times) {
    for (int i = 0; i < times; i++) {
        relax_all();
    }
}

void Field::relax_all() {
    for (auto node : nodes) {
        relax(*node);
    }
}

void Field::relax(Node& node) {
    Force f;
    for (std::weak_ptr<Node> pointing : node.connections_to) {
        f = f + (0.75 * node.force_from(*pointing.lock()));
    }
}

} // namespace oonalysis::graph
