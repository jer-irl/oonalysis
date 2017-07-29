#include <string>
#include <SQLiteCpp.h>
#include "init.h"

void init_db(SQLite::Database db)
{
    db.exec(std::string("CREATE TABLE IF NOT EXISTS file ( ")
          + "id INTEGER PRIMARY KEY, "
          + "filename TEXT NOT NULL"
          + ");");

    db.exec(std::string("CREATE TABLE IF NOT EXISTS cpplinclusion ( ")
          + "id INTEGER PRIMARY KEY, "
          + "FOREIGN KEY (includer) REFERENCES files (id), "
          + "FOREIGN KEY (includee) REFERENCES files (id)"
          + ");");
}
