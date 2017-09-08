#include "point.h"

namespace oonalysis::graph {

bool Point::operator==(const Point& p2) {
    return this->x == p2.x
        && this->y == p2.y
        && this->z == p2.z;
}


} // namespace oonalysis::graph
