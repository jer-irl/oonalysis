#include "PlainEdge.hpp"

#include <boost/algorithm/string.hpp>

namespace oonalysis::graph {

PlainEdge::PlainEdge(const std::string &line) {
    std::vector<std::string> toks;
    boost::split(toks, line, boost::is_any_of(" "));

    if (toks[0] != "edge") { throw std::runtime_error("Bad line into PlainEdge"); }

    char* end_ptr;
    tail = toks[1];
    head = toks[2];
    n = (int) std::strtol(toks[3].c_str(), &end_ptr, 10);

    int base_index = 4;
    for (int i = 0; i < n; i++) {
        int index = base_index + i;

        auto x = (int) std::strtol(toks[index].c_str(), &end_ptr, 10);
        auto y = (int) std::strtol(toks[index + 1].c_str(), &end_ptr, 10);
        control_pts.emplace_back(std::make_pair(x, y));
    }

    int new_base_index = 3 + 2 * n + 1;
    if (toks.size() - new_base_index > 2) {
        std::string name = toks[new_base_index];
        auto label_x = (int) std::strtol(toks[new_base_index + 1].c_str(), &end_ptr, 10);
        auto label_y = (int) std::strtol(toks[new_base_index + 2].c_str(), &end_ptr, 10);
        label = std::make_unique<PlainEdge::EdgeLabel>(name, label_x, label_y);

        new_base_index += 3;
    }

    if (toks.size() - new_base_index > 1) {
        style = toks[new_base_index];
        new_base_index++;
    } else {
        style = "solid";
    }

    color = toks[new_base_index];
}

} // namespace oonalysis::graph