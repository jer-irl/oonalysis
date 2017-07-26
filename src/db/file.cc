#include <string>
#include <sqlite3.h>
#include <stdlib.h>
#include "oonalysis.h"
#include "file.h"

extern sqlite3* oonalysis::DB;

namespace db {

const std::string File::tablename = "file";
const std::string add_cmd = "INSERT INT file VALUES (?)";
sqlite3_stmt* File::add_statement = nullptr;

void File::init_statics()
{
    if (!File::add_statement) {
        int rc;
        rc = sqlite3_prepare(oonalysis::DB, add_cmd.c_str(), 256, &File::add_statement, NULL);
        if (rc) { exit(1); }
    }
}

File::File()
{
    init_statics();
}

File::File(int id)
{
    init_statics();

    // Get existing
}




} // namespace db
