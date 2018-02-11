#ifndef METRICS_FILES_H
#define METRICS_FILES_H

#include <string>
#include <vector>
#include "db/types.h"
#include "db/db.h"

namespace oonalysis::metrics {

std::vector<db::FunctionDef> functions_in_file(db::Database& db, const db::File& f);

} // namespace oonalysis::metrics

#endif // METRICS_FILES_H

