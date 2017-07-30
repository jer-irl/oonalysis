#ifndef DB_H
#define DB_H

#include <SQLiteCpp.h>

#define MAX_FILENAME 256

char DB_NAME[MAX_FILENAME];

#define GET_DB SQLite::Database db(db_name);

#endif // DB_H

