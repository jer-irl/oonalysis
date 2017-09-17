#include "repo/repo.h"
#include "repo/types.h"
#include "functiondecl.h"

namespace oonalysis::db {

bool add_new_function_decl(const std::string& name, const std::string& file) {
    repo::db_function_decl to_add;
    to_add.name = name;
    to_add.file = file;

    return repo::add_dbfunctiondecl(to_add);
}

} // namespace oonalysis::db
