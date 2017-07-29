#include <SQLiteCpp.h>
#include "files.h"

int num_files(SQLite::Database& db)
{
    SQLite::Statement query(db, "SELECT COUNT(*) FROM file)");
    query.executeStep();
    return query.getColumn(0).getInt();
}
