#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include "io.h"

sqlite3* get_db(const char* filename)
{
    sqlite3* res;
    int result_code = sqlite3_open(filename, &res);
    if (result_code) {
        printf("Could not make database\n");
        exit(1);
    }
    return res;
}
