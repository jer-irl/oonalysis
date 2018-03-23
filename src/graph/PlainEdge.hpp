#ifndef GRAPH_PLAINEDGE_HPP
#define GRAPH_PLAINEDGE_HPP

#include <string>
#include <vector>
#include <memory>

namespace oonalysis::graph {


struct PlainEdge {
    struct EdgeLabel;

    PlainEdge(const std::string& line);

    std::string tail;
    std::string head;
    int n;
    std::vector<std::pair<int, int>> control_pts;
    std::unique_ptr<EdgeLabel> label;
    std::string style;
    std::string color;

    struct EdgeLabel {
        EdgeLabel(const std::string& text, int x, int y) : text(text), x(x), y(y) { }
        std::string text;
        int x;
        int y;
    };

};

} // namespace oonalysis::graph

#endif // GRAPH_PLAINEDGE_HPP