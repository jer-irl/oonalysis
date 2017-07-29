#ifndef DBREPO_H
#define DBREPO_H

#include <vector>
#include <SQLiteCpp.h>
#include "dbtypes.h"

bool add_dbfile(SQLite::Database& db, db_file dbfile);
bool get_dbfile(SQLite::Database& db, int id, db_file* dbfile);
bool get_dbfile(SQLite::Database& db, const std::string filename, db_file* dbfile);
std::vector<db_file> get_dbfiles(SQLite::Database& db);
bool update_dbfile(SQLite::Database& db, db_file dbfile, int id);
bool delete_dbfile(SQLite::Database& db, int id);

bool add_dbcppinclusion(SQLite::Database& db, db_cppinclusion inclusion);
bool get_dbcppinclusion(SQLite::Database& db, int id, db_cppinclusion* incl);
std::vector<db_cppinclusion> get_dbcppinclusions(SQLite::Database& db);
bool update_dbcppinclusion(SQLite::Database& db, db_cppinclusion inclusion, int id);
bool delete_dbcppinclusion(SQLite::Database& db, int id);

#endif // DBREPO_H
