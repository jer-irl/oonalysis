#ifndef FILE_H
#define FILE_H

#include <sqlite3.h>

sqlite3* get_db(const char* filename);

#endif // FILE_H
