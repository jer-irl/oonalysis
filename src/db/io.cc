#include <SQLiteCpp/SQLiteCpp.h>
#include "io.hh"

SQLite::Database get_db(const std::string& filename)
{
    if (filename == "") {
        return SQLite::Database res(":memory:");
    } else {
        return SQLite::Database res(filename);
    }
}
