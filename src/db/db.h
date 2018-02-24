#ifndef DB_H
#define DB_H

#include <string>
#include "sqlite_orm/sqlite_orm.h"
#include "types.h"


namespace orm = sqlite_orm;
namespace oonalysis::db {

static inline auto get_storage(const std::string& filename) {
    auto storage = orm::make_storage(filename,
                                     orm::make_table("files",
                                                     orm::make_column("id", &File::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("path", &File::path)
                                     ),
                                     orm::make_table("func_decls",
                                                     orm::make_column("id", &FunctionDecl::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &FunctionDecl::function_name),
                                                     orm::make_column("file_id", &FunctionDecl::file_id),
                                                     orm::make_column("return_type", &FunctionDecl::return_type),
                                                     orm::foreign_key(&FunctionDecl::file_id).references(&File::id)
                                     ),
                                     orm::make_table("var_decls",
                                                     orm::make_column("id", &VarDecl::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &VarDecl::name),
                                                     orm::make_column("type", &VarDecl::type),
                                                     orm::make_column("is_global", &VarDecl::is_global),
                                                     orm::make_column("file_id", &VarDecl::file_id),
                                                     orm::foreign_key(&VarDecl::file_id).references(&File::id)
                                     ),
                                     orm::make_table("func_defs",
                                                     orm::make_column("id", &FunctionDef::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &FunctionDef::function_name),
                                                     orm::make_column("file_id", &FunctionDef::file_id),
                                                     orm::make_column("return_type", &FunctionDef::return_type),
                                                     orm::foreign_key(&FunctionDef::file_id).references(&File::id)
                                     )
    );
    storage.sync_schema(true);
    return storage;
}

using Database = decltype(get_storage(""));

} // namespace oonalysis::db

#endif // DB_H
