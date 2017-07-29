#ifndef FILE_H
#define FILE_H

#include <SQLiteCpp.h>

SQLite::Database* get_db(const std::string& filename);

#endif // FILE_H
