#ifndef GRAPH_GRAPH_HPP
#define GRAPH_GRAPH_HPP

#include <unordered_set>
#include <memory>

namespace oonalysis::graph {

class Node;
class Edge;

struct Point {
    Point(float x, float y) : x(x), y(y) { }
    float x;
    float y;
};

class Graph {
public:
    Graph(std::unordered_set<std::shared_ptr<Node>>& nodes, std::unordered_set<std::shared_ptr<Edge>>& edges);

    virtual void initializeLayout();
    virtual void tick() = 0;

    void addNode(std::shared_ptr<Node> node);
    void addEdge(std::shared_ptr<Edge> edge);

protected:
    std::unordered_set<std::shared_ptr<Node>> nodes;
    std::unordered_set<std::shared_ptr<Edge>> edges;
};

class Node {
public:
    Node();

    void addIncomingEdge(std::shared_ptr<Edge>);
    void removeIncomingEdge(std::shared_ptr<Edge>);
    void addOutgoingEdge(std::shared_ptr<Edge>);
    void removeOutgoingEdge(std::shared_ptr<Edge>);

    Point position;
    Point velocity;

    virtual bool containsPoint(Point p) = 0;

protected:
    std::unordered_set<std::shared_ptr<Edge>> incomingEdges;
    std::unordered_set<std::shared_ptr<Edge>> outgoingEdges;
};

class Edge {
public:
    Edge(std::shared_ptr<Node> begin, std::shared_ptr<Node> end) : begin(begin), end(end) { }

protected:
    std::shared_ptr<Node> begin;
    std::shared_ptr<Node> end;
};

} // namespace oonalysis::graph

#endif // GRAPH_GRAPH_HPP