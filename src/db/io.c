#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "io.h"

sqlite3* get_db(const char* filename)
{
    sqlite3* res;
    int rc;
    if (filename) {
        rc = sqlite3_open(filename, &res);
    } else {
        rc = sqlite3_open(":memory:", &res);
    }

    if (rc) {
        printf("Could not make database\n");
        exit(1);
    }
    return res;
}
