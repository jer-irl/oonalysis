#ifndef DB_H
#define DB_H

#include "SQLiteCpp/SQLiteCpp.h"

#define MAX_FILENAME 256
SQLite::Database DB;

#define FILE_TABLE table
#define CPPINCLUSION_TABLE cppinclusion

#endif // DB_H

