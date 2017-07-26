#include <stdio.h>
#include <sqlite3.h>

bool add_file(sqlite3* db, const char* filename)
{
    int rc;
    char* error_msg;

    // See if file already added
    sqlite3_stmt* statement;
    rc = sqlite3_prepare(db, "SELECT id FROM file WHERE filename = ?", 256, &statement, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_text(statement, 1, filename, -1, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_step(statement);
    sqlite3_finalize(statement);
    if (rc == SQLITE_DONE) { return false; }

    // File not already added
    rc = sqlite3_prepare(db, "INSERT INTO file VALUES (?))", filename)

fail:
    printf("%s\n", error_msg);
    exit(1);
}

bool add_cppinclusion(sqlite3* db, const char* includer, const char* includee)
{
}
