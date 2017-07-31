#ifndef DB_H
#define DB_H

#include <SQLiteCpp.h>


namespace oonalysis {
namespace db {

#define MAX_FILENAME 256

char DB_NAME[MAX_FILENAME];

#define GET_DB SQLite::Database db(db_name);

} // namespace db
} // namespace oonalysis

#endif // DB_H
