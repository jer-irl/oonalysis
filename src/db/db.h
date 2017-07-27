#ifndef DB_H
#define DB_H

#include <sqlite3.h>

#define MAX_FILENAME 256
sqlite3* DB;

#define FILE_TABLE table
#define CPPINCLUSION_TABLE cppinclusion

#endif // DB_H

