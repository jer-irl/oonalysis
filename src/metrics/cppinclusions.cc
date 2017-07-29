#include "cppinclusions.h"

uint32_t num_cppinclusions(SQLite::Database& db)
{
    SQLite::Statement query(db, "SELECT COUNT(*) FROM cppinclusions;");
    query.executeStep();
    return query.getColumn(0).getInt();
}

