#include "files.h"

#include <iostream>
#include "sqlite_orm/sqlite_orm.h"
#include "db/db.h"
#include "db/types.h"

namespace orm = sqlite_orm;
namespace oonalysis::metrics {

std::vector<db::FunctionDef> functions_in_file(db::Database& db, const db::File& f) {
    return db.get_all<db::FunctionDef>(orm::where(orm::is_equal(&db::FunctionDef::file_id, f.id)));
}

} // namespace oonalysis::metrics
