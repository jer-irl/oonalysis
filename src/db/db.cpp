#include "db.h"

#include "sqlite_orm/sqlite_orm.h"
#include "types.h"

namespace oonalysis::db {

using namespace sqlite_orm;

Database get_storage(const std::string& filename) {
    return make_storage(filename,
                        make_table("files",
                                   make_column("id", &File::id, autoincrement(), primary_key()),
                                   make_column("path", &File::path)
                        ),
                        make_table("funcdefs",
                                   make_column("id", &FunctionDef::id, autoincrement(), primary_key()),
                                   make_column("name", &FunctionDef::function_name),
                                   make_column("file_id", &FunctionDef::file_id),
                                   foreign_key(&FunctionDef::file_id).references(&File::id)
                        )
    );
}


} // namespace oonalysis::db