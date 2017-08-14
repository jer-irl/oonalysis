#include <SQLiteCpp.h>
#include "files.h"

namespace oonalysis::metrics {

uint32_t num_files(SQLite::Database& db)
{
    SQLite::Statement query(db, "SELECT COUNT(*) FROM file)");
    query.executeStep();
    return query.getColumn(0).getInt();
}

void main_files()
{
    // TODO
}

} // namespace oonalysis::metrics
