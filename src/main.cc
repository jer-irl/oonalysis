#include <string>
#include <sqlite3.h>
#include "oonalysis.h"

extern "C" {
#include "db/io.h"
#include "db/init.h"
}

int main(int argc, char** argv)
{
    sqlite3* db = get_db("tmptest.db");
    init_db(db);

    return 0;
}
