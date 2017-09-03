#ifndef GRAPH_EDGE_H
#define GRAPH_EDGE_H

#include <memory>
#include "node.h"

namespace oonalysis::graph {

struct Node;
struct Edge {
    std::weak_ptr<Node> A;
    std::weak_ptr<Node> B;
    float distance() const;
}; // struct Edge

} // namespace oonalysis::graph

#endif // GRAPH_EDGE_H
