#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <sqlite3.h>
#include "init.h"

void init_db(sqlite3* db)
{
    int return_code;
    char* error_msg;

    return_code = sqlite3_exec(
            db,
            "CREATE TABLE IF NOT EXISTS cpp_inclusions (id INTEGER PRIMARY KEY, filename TEXT NOT NULL)",
            NULL,
            NULL,
            &error_msg);
    if (return_code) {
        printf("%s\n", error_msg);
        exit(1);
    }

    sqlite3_exec(
            db,
            "CREATE TABLE IF NOT EXISTS cpp_inclusions (id INTEGER PRIMARY KEY, FOREIGN KEY (includer) REFERENCES files (id), FOREIGN KEY (includee) REFERENCES files (id)",
            NULL,
            NULL,
            &error_msg);
    if (return_code) {
        printf("%s\n", error_msg);
        exit(1);
    }

}
