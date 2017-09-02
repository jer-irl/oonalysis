#ifndef GRAPH_FIELD_H
#define GRAPH_FIELD_H

#include <vector>
#include "node.h"
#include "edge.h"

namespace oonalysis::graph {

class Field {
public:
    Field(float xsize, float ysize, float zsize, std::vector<Node> nodes, std::vector<Edge> edges);
    void relax();
    void relax(Node& node);

    std::vector<Node> nodes;
    std::vector<Edge> edges;

private:
    float xsize, ysize, zsize;

}; // class Field

} // namespace oonalysis::graph

#endif // GRAPH_FIELD_H
