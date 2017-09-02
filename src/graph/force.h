#ifndef GRAPH_FORCE_H
#define GRAPH_FORCE_H

#include <vector>
#include "point.h"

namespace oonalysis::graph {

struct Force : public Point {
    Force(std::vector<Force>);
}; // struct Force

} // namespace oonalysis::graph

#endif // GRAPH_FORCE_H
