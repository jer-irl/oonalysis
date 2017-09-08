#include <algorithm>
#include <memory>
#include <random>
#include "node.h"
#include "force.h"

namespace oonalysis::graph {

Node::Node() {
    std::default_random_engine generator;
    std::uniform_real_distribution<float> distribution(0, 100);

    this->x = distribution(generator);
    this->y = distribution(generator);
    this->z = distribution(generator);
    this->weight = 1;
}

Force Node::force_from(Node& n) {
    Force res;

    for (auto ptr : this->connections_to) {
        if (n == *ptr.lock()) {
            res = res + attractive_force(*this, n);
            break;
        }
    }

    res = res + repulsive_force(*this, n);

    return res;
}

} // namespace oonalysis::graph
