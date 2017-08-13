#ifndef METRICS_CPPINCLUSIONS_H
#define METRICS_CPPINCLUSIONS_H

#include <SQLiteCpp.h>

namespace oonalysis::metrics {

void main_cppinclusions();

uint32_t num_cppinclusions(SQLite::Database& db);
float avg_num_cppinclusions();

} // namespace oonalysis::metrics

#endif // METRICS_CPPINCLUSIONS_H

