#include <SQLiteCpp.h>
#include "dbtypes.h"
#include "dbrepo.h"

bool add_dbfile(SQLite::Database db, db_file f)
{
    // See if file already added
    if (f.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM FILE_TABLE WHERE id = ?");
        query.bind(f.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    // File not already added
    std::string stmt = "INSERT INTO file VALUES (" + f.filename + ");";

    db.exec(stmt);

    return true;
}

bool add_dbcppinclusion(SQLite::Database db, db_cppinclusion incl)
{
    // See if file already added
    if (incl.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM cppinclusion WHERE id = ?");
        query.bind(incl.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    // File not already added
    std::string stmt = "INSERT INTO file VALUES (" + incl.includer + ", " + incl.includee + ");";

    db.exec(stmt);

    return true;
}
