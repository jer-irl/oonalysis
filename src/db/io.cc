#include <SQLiteCpp.h>
#include "io.h"

SQLite::Database* get_db(const std::string& filename)
{
    if (filename == "") {
        return new SQLite::Database(":memory:", SQLite::OPEN_CREATE);;
    } else {
        return new SQLite::Database(filename);
    }
}
