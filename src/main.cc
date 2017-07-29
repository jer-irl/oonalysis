#include <string>
#include <SQLiteCpp.h>
#include "oonalysis.h"
#include "db/io.h"
#include "db/init.h"

int main(int argc, char** argv)
{
    SQLite::Database* db = get_db("tmptest.db");
    init_db(&db);

    return 0;
}
