#ifndef GRAPH_LAYOUT_H
#define GRAPH_LAYOUT_H

#include <vector>
#include "node.h"
#include "edge.h"
#include "field.h"

namespace oonalysis::graph {

void force_directed(Field field, std::vector<Node> nodes, std::vector<Edge> edges);

} // namespace oonalysis::graph

#endif // GRAPH_LAYOUT_H
