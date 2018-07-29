#ifndef GRAPH_FORCEDIRECTEDGRAPH_HPP
#define GRAPH_FORCEDIRECTEDGRAPH_HPP

#include "Graph.hpp"

namespace oonalysis::graph {

class ForceDirectedGraph : public Graph {
public:
    ForceDirectedGraph(std::unordered_set<std::shared_ptr<Node>>& nodes,
                       std::unordered_set<std::shared_ptr<Edge>>& edges,
                       int width,
                       int height);

    virtual void initializeLayout();
    virtual void tick() = 0;

private:
    int width;
    int height;
};

} // namespace oonalysis::graph

#endif // GRAPH_FORCEDIRECTEDGRAPH_HPP