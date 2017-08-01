#include <string>
#include <SQLiteCpp.h>
#include "init.h"
#include "db.h"

namespace oonalysis {
namespace db {

extern char DB_NAME[256];

void set_db_name(const std::string& name)
{
    strncpy(DB_NAME, name.c_str(), 256);
    SQLite::Database db(DB_NAME, SQLite::OPEN_CREATE | SQLite::OPEN_READWRITE);
}

void init_db()
{
    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    db.exec(
            "CREATE TABLE IF NOT EXISTS file ( "
            "id INTEGER PRIMARY KEY, "
            "filename TEXT NOT NULL"
            ");"
    );

    db.exec(
            "CREATE TABLE IF NOT EXISTS cppinclusion ( "
            "id INTEGER PRIMARY KEY, "
            "includer INTEGER, "
            "includee INTEGER, "
            "FOREIGN KEY (includer) REFERENCES file (id), "
            "FOREIGN KEY (includee) REFERENCES file (id)"
            ");"
    );
}

} // namespace db
} // namespace oonalysis
