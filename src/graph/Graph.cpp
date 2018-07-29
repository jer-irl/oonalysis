#include "Graph.hpp"

namespace oonalysis::graph {

Graph::Graph(std::unordered_set<std::shared_ptr<Node>>& nodes,
             std::unordered_set<std::shared_ptr<Edge>>& edges)
        : nodes(nodes), edges(edges) {
    initializeLayout();
}

void Graph::initializeLayout() {
}

void Graph::addEdge(std::shared_ptr<Edge> edge) {
    edges.insert(edge);
}

void Graph::addNode(std::shared_ptr<Node> node) {
    nodes.insert(node);
}

void Node::addIncomingEdge(std::shared_ptr<Edge> e) {
    incomingEdges.insert(e);
}

Node::Node() : position(Point(0, 0)), velocity(Point(0, 0)) {
}

void Node::removeIncomingEdge(std::shared_ptr<Edge> e) {
    incomingEdges.erase(e);
}

void Node::addOutgoingEdge(std::shared_ptr<Edge> e) {
    outgoingEdges.insert(e);
}

void Node::removeOutgoingEdge(std::shared_ptr<Edge> e) {
    outgoingEdges.erase(e);
}

} // namespace oonalysis::graph