#include <string>
#include <memory>
#include "file.h"
#include "repo/types.h"
#include "repo/repo.h"

namespace oonalysis::db {

bool add_new_file(const std::string& filename, int* loc)
{
    if(repo::dbfile_present(filename)) {
        return false;
    }

    repo::db_file dbfile;
    dbfile.filename = filename;

    if (loc) {
        dbfile.loc = *loc;
    } else {
        dbfile.loc = -1;
    }

    repo::add_dbfile(dbfile);
    return true;
}

bool update_loc(const std::string& filename, int loc)
{
    if (!repo::dbfile_present(filename)) {
        return false;
    }

    std::shared_ptr<repo::db_file> existing = repo::get_dbfile(filename);
    existing->loc = loc;

    return update_dbfile(existing->id, *existing);
}

int loc_in_file(const std::string& filename)
{
    std::shared_ptr<repo::db_file> retrieved = repo::get_dbfile(filename);
    return retrieved->loc;
}

} // namespace oonalysis::db
