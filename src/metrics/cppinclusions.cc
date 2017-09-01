#include <iostream>
#include "db/cppinclusion.h"
#include "cppinclusions.h"

namespace oonalysis::metrics {

void main_cppinclusions() {
    std::cout << "Metrics for C preprocessor inclusions:" << std::endl;
    std::cout << "Average inclusions: " << db::avg_num_cppinclusions() << std::endl;
    return;
}

} // namespace oonalysis::metrics
