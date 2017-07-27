#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <sqlite3.h>
#include "dbtypes.h"

extern sqlite3* DB;

bool add_dbfile(db_file f)
{
    int rc;
    char* error_msg;
    sqlite3_stmt* statement;

    // See if file already added
    if (f.id != 0) {
        rc = sqlite3_prepare(DB, "SELECT id FROM FILE_TABLE WHERE id = ?", 256, &statement, NULL);
        if (rc) { goto fail; }
        rc = sqlite3_bind_int(statement, 1, f.id);
        if (rc) { goto fail; }
        rc = sqlite3_step(statement);
        sqlite3_finalize(statement);
        if (rc != SQLITE_DONE) { return false; }
    }

    // File not already added
    rc = sqlite3_prepare(DB, "INSERT INTO file VALUES (?))", 256, &statement, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_text(statement, 1, f.filename, -1, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) { goto fail; }

    return true;

fail:
    printf("%s\n", error_msg);
    exit(1);
}

bool add_dbcppinclusion(db_cppinclusion incl)
{
    int rc;
    char* error_msg;
    sqlite3_stmt* statement;

    // See if file already added
    if (incl.id != 0) {
        rc = sqlite3_prepare(DB, "SELECT id FROM FILE_TABLE WHERE id = ?", 256, &statement, NULL);
        if (rc) { goto fail; }
        rc = sqlite3_bind_int(statement, 1, incl.id);
        if (rc) { goto fail; }
        rc = sqlite3_step(statement);
        sqlite3_finalize(statement);
        if (rc != SQLITE_DONE) { return false; }
    }

    // File not already added
    rc = sqlite3_prepare(DB, "INSERT INTO file VALUES (?, ?))", 256, &statement, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_text(statement, 1, incl.includer, -1, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_text(statement, 1, incl.includee, -1, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) { goto fail; }

    return true;

fail:
    printf("%s\n", error_msg);
    exit(1);
}
