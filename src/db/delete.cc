#include <SQLiteCpp.h>
#include "dbrepo.h"


namespace oonalysis::db {

bool delete_dbfile(SQLite::Database& db, int id)
{
    db.exec("DELETE FROM file WHERE id = " + std::to_string(id));
    return true;
}

bool delete_dbcppinclusion(SQLite::Database& db, int id)
{
    db.exec("DELETE FROM cppinclusion WHERE id = " + std::to_string(id));
    return true;
}

} // namespace oonalysis::db
