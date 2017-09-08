#ifndef GRAPH_POINT_H
#define GRAPH_POINT_H

namespace oonalysis::graph {

struct Point {
    float x, y, z;

protected:
    bool operator==(const Point& p2);
}; // struct Point

} // namespace oonalyisis::graph

#endif // GRAPH_POINT_H
