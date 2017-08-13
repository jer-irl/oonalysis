#include <SQLiteCpp.h>
#include "dbtypes.h"
#include "dbrepo.h"
#include "db.h"
extern "C" {
#include "util/log.h"
}

namespace oonalysis::db {

bool add_dbfile(db_file f)
{
    LOG(DEBUG, "Adding db_file");

    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);
    // See if file already added
    if (f.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM FILE_TABLE WHERE id = ?");
        query.bind(f.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    // File not already added
    std::string stmt = "INSERT INTO file VALUES ('" + f.filename + "');";

    db.exec(
            "INSERT INTO file (filename) VALUES ('"
          + f.filename
          + "');"
            );

    return true;
}

bool add_dbcppinclusion(db_cppinclusion incl)
{
    LOG(DEBUG, "Adding db_cppinclusion");

    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);
    // See if file already added
    if (incl.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM cppinclusion WHERE id = ?");
        query.bind(incl.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    db.exec(
            "INSERT INTO cppinclustion (includer, includee) VALUES ('"
          + incl.includer
          + "', '"
          + incl.includee
          + "');");

    return true;
}

} // namespace oonalysis::db
