#ifndef OONALYSIS_H
#define OONALYSIS_H

#include <sqlite3.h>


namespace oonalysis {

sqlite3* DB;

enum Lang
{
    C, CPP, PY, HS, NONE, OTHER, UNKNOWN,
};

} // namespace oonalysis

#endif // OONALYSIS_H
