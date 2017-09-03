#ifndef GRAPH_NODE_H
#define GRAPH_NODE_H

#include <memory>
#include <vector>
#include "edge.h"
#include "point.h"

namespace oonalysis::graph {

struct Edge;

struct Node : public Point {
    Node(float x, float y, float z, float weight);
    float weight;
    std::vector<std::weak_ptr<Edge>> edges;
};

} // namespace oonalysis::graph

#endif // GRAPH_NODE_H
