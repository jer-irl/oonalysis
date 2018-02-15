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
                                make_table("func_decls",
                                           make_column("id", &FunctionDecl::id, autoincrement(), primary_key()),
                                           make_column("name", &FunctionDecl::function_name),
                                           make_column("file_id", &FunctionDecl::file_id),
                                           make_column("return_type", &FunctionDecl::return_type),
                                           foreign_key(&FunctionDecl::file_id).references(&File::id)
                                ),
                                make_table("var_decls",
                                           make_column("id", &VarDecl::id, autoincrement(), primary_key()),
                                           make_column("name", &VarDecl::name),
                                           make_column("type", &VarDecl::type),
                                           make_column("is_global", &VarDecl::is_global),
                                           make_column("file_id", &VarDecl::file_id),
                                           foreign_key(&VarDecl::file_id).references(&File::id)
                                )
    );
    storage.sync_schema(true);
    return storage;
}


} // namespace oonalysis::db