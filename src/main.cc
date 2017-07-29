#include <string>
#include <SQLiteCpp.h>
#include "oonalysis.h"
#include "db/io.h"
#include "db/init.h"

int main(int argc, char** argv)
{
    SQLite::Database db(":memory:", SQLite::OPEN_CREATE);
    init_db(db);

    return 0;
}
