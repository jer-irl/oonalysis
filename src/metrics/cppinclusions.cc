#include "files.h"
#include "cppinclusions.h"

namespace oonalysis::metrics {

uint32_t num_cppinclusions(SQLite::Database& db)
{
    SQLite::Statement query(db, "SELECT COUNT(*) FROM cppinclusions;");
    query.executeStep();
    return query.getColumn(0).getInt();
}

float avg_num_cppinclusions(SQLite::Database& db)
{
    return num_cppinclusions(db) / num_files();
}

void main_cppinclusions()
{
    // TODO
}

} // namespace oonalysis::metrics
