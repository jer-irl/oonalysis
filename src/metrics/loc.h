#ifndef METRICS_LOC_H
#define METRICS_LOC_H

#include <fstream>

namespace oonalysis::metrics {

void main_loc();

uint32_t loc_in_file(std::ifstream file);

} // namespace oonalysis::metrics

#endif // METRICS_LOC_H
