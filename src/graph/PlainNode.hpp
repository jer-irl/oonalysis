#ifndef GRAPH_PLAINNODE_HPP
#define GRAPH_PLAINNODE_HPP

#include <string>

namespace oonalysis::graph {

struct PlainNode {

    explicit PlainNode(const std::string& line);

    std::string name;
    int x;
    int y;
    int width;
    int height;
    std::string label;
    std::string style;
    std::string shape;
    std::string color;
    std::string fillcolor;
};

} // namespace oonalysis::graph

#endif // GRAPH_PLAINNODE_HPP