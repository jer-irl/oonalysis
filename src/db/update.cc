#include <SQLiteCpp.h>
#include "dbrepo.h"

bool update_dbfile(SQLite::Database db, db_file dbfile, int id)
{
    // See if file already added
    if (dbfile.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM FILE_TABLE WHERE id = ?");
        query.bind(dbfile.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    db.exec("UPDATE TABLE file SET filename = " + dbfile.filename + " WHERE id = " + std::to_string(id));
    return true;
}

bool update_dbcppinclusion(SQLite::Database db, db_cppinclusion incl, int id)
{
    // See if file already added
    if (incl.id != 0) {
        SQLite::Statement query(db, "SELECT id FROM cppinclusion WHERE id = ?");
        query.bind(incl.id);
        query.executeStep();
        if (!query.isDone()) { return false; }
    }

    db.exec(std::string("UPDATE TABLE file SET ")
          + "includer = " + incl.includer + ", "
          + "includee = " + incl.includee + " "
          + "WHERE id = " + std::to_string(id)
          + ";");
    return true;
}
