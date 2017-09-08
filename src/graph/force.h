#ifndef GRAPH_FORCE_H
#define GRAPH_FORCE_H

#include <vector>
#include "point.h"
#include "node.h"

namespace oonalysis::graph {

struct Node;

struct Force : public Point {
    Force operator+(const Force& f) const;
    Force operator-(const Force& f) const;
    void operator+=(const Force& f);
}; // struct Force

Force attractive_force(const Node& a, const Node& b);
Force repulsive_force(const Node& a, const Node& b);
Force operator*(const double num, const Force& f);

} // namespace oonalysis::graph

#endif // GRAPH_FORCE_H
