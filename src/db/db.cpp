#include "db.h"

#include "sqlite_orm/sqlite_orm.h"
#include "types.h"

namespace oonalysis::db {

using namespace sqlite_orm;

Database get_storage(const std::string& filename) {
    auto storage = make_storage(filename,
                                make_table("files",
                                           make_column("id", &File::id, autoincrement(), primary_key()),
                                           make_column("path", &File::path)
                                ),
                                make_table("funcdecls",
                                           make_column("id", &FunctionDecl::id, autoincrement(), primary_key()),
                                           make_column("name", &FunctionDecl::function_name),
                                           make_column("file_id", &FunctionDecl::file_id),
                                           foreign_key(&FunctionDecl::file_id).references(&File::id)
                                )
    );
    storage.sync_schema(true);
    storage.remove_all<FunctionDecl>();
    storage.remove_all<File>();
    return storage;
}


} // namespace oonalysis::db