#include <string>
#include <vector>
#include <SQLiteCpp.h>
#include "db.h"
#include "dbrepo.h"

extern sqlite3* DB;

bool get_dbfile(SQLite::Database db, int id, db_file* dbfile)
{
    SQLite::Statement stmt(db, "SELECT filename FROM file WHERE id = " + std::to_string(id));

    stmt.executeStep();

    dbfile->id = id;
    dbfile->filename = stmt.getColumn(0).getText();
    return true;
}

std::vector<db_file> get_dbfiles(SQLite::Database db)
{
    std::vector<db_file> res;
    SQLite::Statement stmt(db, "SELECT id, filename FROM file");

    while (stmt.executeStep()) {
        db_file retrieved;
        retrieved.id = stmt.getColumn(0).getInt();
        retrieved.filename = stmt.getColumn(1).getText();
        res.push_back(retrieved);
    }

    return res;
}


bool get_dbcppinclusion(SQLite::Database db, int id, db_cppinclusion* incl)
{
    SQLite::Statement stmt(db, "SELECT includer, includee FROM file WHERE id = " + std::to_string(id));

    stmt.executeStep();

    incl->id = id;
    incl->includer = stmt.getColumn(0).getText();
    incl->includee = stmt.getColumn(1).getText();
    return true;
}

std::vector<db_cppinclusion> get_dbcppinclusions(SQLite::Database db)
{
    std::vector<db_cppinclusion> res;
    SQLite::Statement stmt(db, "SELECT id, includer, includee FROM cppinclusion");

    while (stmt.executeStep()) {
        db_cppinclusion retrieved;
        retrieved.id = stmt.getColumn(0).getInt();
        retrieved.includer = stmt.getColumn(1).getText();
        retrieved.includee = stmt.getColumn(2).getText();
        res.push_back(retrieved);
    }

    return res;
}

