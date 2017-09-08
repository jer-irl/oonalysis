#include "node.h"
#include "force.h"

namespace oonalysis::graph {

Force Force::operator+(const Force& a) const {
    Force f;
    f.x = a.x + x;
    f.y = a.y + y;
    f.z = a.z + z;
    return f;
}

Force Force::operator-(const Force& a) const {
    Force f;
    f.x = x - a.x;
    f.y = y - a.y;
    f.z = z - a.z;
    return f;
}

float attractive_force(float a, float b) {
    // F = -kx
    return - 20 * (a - b > 0 ? a - b : b - a);
}

float repulsive_force(float a, float b) {
    // F = kqq / r^2
    return 20 / ((a - b > 0 ? a - b : b - a)
               * (a - b > 0 ? a - b : b - a));
}

Force operator+=(Force f1, const Force& f2) {
    return f1 + f2;
}

Force operator*(double num, const Force& f) {
    Force res = f;
    res.x *= num;
    res.y *= num;
    res.z *= num;

    return res;
}

Force attractive_force(const Node& a, const Node& b) {
    return {
        {attractive_force(a.x, b.x),
         attractive_force(a.y, b.y),
         attractive_force(a.z, b.z)},
    };
}

Force repulsive_force(const Node& a, const Node& b) {
    return {
        {repulsive_force(a.x, b.x),
         repulsive_force(a.y, b.y),
         repulsive_force(a.z, b.z)},
    };
}

} // namespace oonalysis::graph
