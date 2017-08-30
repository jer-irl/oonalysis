#include <string>
#include <vector>
#include <SQLiteCpp.h>
#include "db.h"
#include "repo.h"


namespace oonalysis::db::repo {

/* ======================================== */
/* Presence Checks */
/* ======================================== */

bool dbfile_present(int id) {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READONLY);
    SQLite::Statement stmt(db, "SELECT id FROM file WHERE id = " + std::to_string(id));

    return stmt.executeStep();
}

bool dbfile_present(const std::string& filename) {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READONLY);
    SQLite::Statement stmt(db, "SELECT id FROM file WHERE filename = ?");
    stmt.bind(1, filename);

    return stmt.executeStep();
}

bool dbcppinclusion_present(const std::string& includer, const std::string& includee) {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READONLY);
    SQLite::Statement stmt(db,
            "SELECT id FROM cppinclusion WHERE includer = ? "
            "AND includee = ?;");
    stmt.bind(1, includer);
    stmt.bind(2, includee);

    return stmt.executeStep();
}


/* ======================================== */
/* Statistics */
/* ======================================== */
uint32_t max_loc() {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READONLY);
    SQLite::Statement stmt(db, "SELECT MAX(loc) FROM file");

    stmt.executeStep();
    uint32_t res = stmt.getColumn(1).getInt();
    stmt.reset();

    return res;
}

float avg_loc() {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READONLY);
    SQLite::Statement stmt(db, "SELECT AVG(loc) FROM file");

    stmt.executeStep();
    float res = stmt.getColumn(1).getDouble();
    stmt.reset();

    return res;
}


/* ======================================== */
/* Retrieval */
/* ======================================== */

std::shared_ptr<db_file> get_dbfile(int id) {
    if (!dbfile_present(id)) {
        return nullptr;
    }

    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    auto res = std::make_shared<db_file>();

    SQLite::Statement stmt(db, "SELECT filename, loc FROM file WHERE id = " + std::to_string(id));

    bool present = stmt.executeStep();
    if (!present) {
        return nullptr;
    }

    res->id = id;
    res->filename = stmt.getColumn(0).getText();
    res->loc = stmt.getColumn(1).getInt();
    return res;
}

std::shared_ptr<db_file> get_dbfile(const std::string& filename) {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    SQLite::Statement stmt(db, "SELECT id, filename, loc FROM file WHERE filename = " + filename);

    stmt.executeStep();

    auto dbfile = std::make_shared<db_file>();
    dbfile->id = stmt.getColumn(0).getInt();
    dbfile->filename = stmt.getColumn(1).getText();
    dbfile->loc = stmt.getColumn(2).getInt();
    return dbfile;
}

std::vector<std::shared_ptr<db_file>> get_dbfiles() {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    std::vector<std::shared_ptr<db_file>> res;
    SQLite::Statement stmt(db, "SELECT id, filename FROM file");

    while (stmt.executeStep()) {
        auto retrieved = std::make_shared<db_file>();
        retrieved->id = stmt.getColumn(0).getInt();
        retrieved->filename = stmt.getColumn(1).getText();
        res.push_back(retrieved);
    }

    return res;
}


bool get_dbcppinclusion(int id, db_cppinclusion* incl) {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    SQLite::Statement stmt(db, "SELECT includer, includee FROM file WHERE id = " + std::to_string(id));

    stmt.executeStep();

    incl->id = id;
    incl->includer = stmt.getColumn(0).getText();
    incl->includee = stmt.getColumn(1).getText();
    return true;
}

std::vector<std::shared_ptr<db_cppinclusion>> get_dbcppinclusions() {
    SQLite::Database db(DB_NAME, SQLite::OPEN_READWRITE);

    std::vector<std::shared_ptr<db_cppinclusion>> res;

    SQLite::Statement stmt(db, "SELECT id, includer, includee FROM cppinclusion");

    while (stmt.executeStep()) {
        auto retrieved = std::make_shared<db_cppinclusion>();
        retrieved->id = stmt.getColumn(0).getInt();
        retrieved->includer = stmt.getColumn(1).getText();
        retrieved->includee = stmt.getColumn(2).getText();
        res.push_back(retrieved);
    }

    return res;
}

} // namespace oonalysis::db::repo
