#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <memory>
#include <vector>
#include "point.h"

namespace oonalysis::graph {

struct Node : public Point {
    Node(float x, float y, float z, float weight);
    Node();
    float weight;
    std::vector<std::weak_ptr<Node>> connections_to;
};

} // namespace oonalysis::graph

#endif // GRAPH_NODE_H
