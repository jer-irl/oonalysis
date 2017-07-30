#ifndef OONALYSIS_H
#define OONALYSIS_H

#include <SQLiteCpp.h>

namespace oonalysis {

char DB_NAME[256];

#define GET_DB SQLite::Database db(db_name);

enum Lang
{
    C, CPP, PY, HS, NONE, OTHER, UNKNOWN,
};

} // namespace oonalysis

#endif // OONALYSIS_H
