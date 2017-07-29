#ifndef METRICS_CPPINCLUSIONS_H
#define METRICS_CPPINCLUSIONS_H

#include <SQLiteCpp.h>

uint32_t num_cppinclusions(SQLite::Database& db);
float avg_num_cppinclusions();

#endif // METRICS_CPPINCLUSIONS_H

