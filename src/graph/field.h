#ifndef GRAPH_FIELD_H
#define GRAPH_FIELD_H

#include <vector>
#include <memory>
#include "node.h"

namespace oonalysis::graph {

class Field {
public:
    Field(float xsize, float ysize, float zsize, std::vector<std::shared_ptr<Node>> nodes);
    void relax_all(int times);

    std::vector<Node> nodes;

private:
    float xsize, ysize, zsize;
    void relax(Node& node);
    void relax_all();

}; // class Field

} // namespace oonalysis::graph

#endif // GRAPH_FIELD_H
