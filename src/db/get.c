#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "db.h"
#include "dbrepo.h"

extern sqlite3* DB;

bool get_dbfile(int id, db_file* dbfile)
{
    int rc;
    char* error_msg;
    const char* text;
    sqlite3_stmt* statement;

    rc = sqlite3_prepare(DB, "SELECT filename FROM FILE_TABLE WHERE id = ?", 256, &statement, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_int(statement, 1, id);
    if (rc) { printf("Couldn't bind\n"); exit(1); }

    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) { printf("unexpected result\n"); exit(1); };

    dbfile->id = id;
    text = (const char *) sqlite3_column_text(statement, 1);
    strncpy(dbfile->filename, text, 256);
    sqlite3_finalize(statement);

    return true;

fail:
    printf("%s\n", error_msg);
    exit(1);
}


bool get_dbcppinclusion(int id, db_cppinclusion* incl)
{
    int rc;
    char* error_msg;
    const char* text;
    sqlite3_stmt* statement;

    rc = sqlite3_prepare(DB, "SELECT includer, includee FROM FILE_TABLE WHERE id = ?", 256, &statement, NULL);
    if (rc) { goto fail; }
    rc = sqlite3_bind_int(statement, 1, id);
    if (rc) { printf("Couldn't bind\n"); exit(1); }

    rc = sqlite3_step(statement);
    if (rc != SQLITE_DONE) { printf("unexpected result\n"); exit(1); };

    incl->id = id;
    text = (const char *) sqlite3_column_text(statement, 1);
    strncpy(incl->includer, text, 256);
    text = (const char *) sqlite3_column_text(statement, 2);
    strncpy(incl->includee, text, 256);
    sqlite3_finalize(statement);

    return true;

fail:
    printf("%s\n", error_msg);
    exit(1);
}
