#include "ForceDirectedGraph.hpp"

#include <random>

namespace oonalysis::graph {

ForceDirectedGraph::ForceDirectedGraph(std::unordered_set<std::shared_ptr<oonalysis::graph::Node>> &nodes,
                                       std::unordered_set<std::shared_ptr<oonalysis::graph::Edge>> &edges,
                                       int width,
                                       int height)
        : Graph(nodes, edges), width(width), height(height) {
}

void ForceDirectedGraph::initializeLayout() {
    std::random_device randomDevice;
    auto engine = std::default_random_engine(randomDevice());
    auto xDist = std::uniform_real_distribution(0, this->width);
    auto yDist = std::uniform_real_distribution(0, this->height);
    for (const std::shared_ptr<Node>& node : nodes) {
        node->position.x = xDist(engine);
        node->position.y = yDist(engine);
    }
}

void ForceDirectedGraph::tick() {
    for (const std::shared_ptr<Node>& node : nodes) {
        Point force(0, 0);
    }
}

} // namespace oonalysis::graph