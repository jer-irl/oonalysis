#include "PlainNode.hpp"

#include <boost/algorithm/string.hpp>

namespace oonalysis::graph {

PlainNode::PlainNode(const std::string &line) {
    std::vector<std::string> toks;
    boost::split(toks, line, boost::is_any_of(" "));

    if (toks[0] != "node") { throw std::runtime_error("non-node line passed in"); }

    char* end_ptr;

    name = toks[1];
    x = (int) std::strtol(toks[2].c_str(), &end_ptr, 10);
    y = (int) std::strtol(toks[3].c_str(), &end_ptr, 10);
    width = (int) std::strtol(toks[4].c_str(), &end_ptr, 10);
    height = (int) std::strtol(toks[5].c_str(), &end_ptr, 10);
    label = toks[6];
    style = toks[7];
    shape = toks[8];
    color = toks[9];
    fillcolor = toks[10];
}

} // namespace oonalysis::graph