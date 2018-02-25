#ifndef DB_H
#define DB_H

#include <string>
#include "sqlite_orm/sqlite_orm.h"
#include "types.h"


namespace oonalysis::db {

static inline auto get_storage(const std::string& filename) {
    namespace orm = sqlite_orm;
    auto storage = orm::make_storage(filename,
                                     orm::make_table("files",
                                                     orm::make_column("path", &File::path, orm::primary_key())
                                     ),
                                     orm::make_table("c_inclusions",
                                                     orm::make_column("includer_path", &CppInclusion::includer_path),
                                                     orm::make_column("includee_path", &CppInclusion::includee_path),
                                                     orm::primary_key(&CppInclusion::includer_path, &CppInclusion::includee_path),
                                                     orm::foreign_key(&CppInclusion::includer_path).references(&File::path),
                                                     orm::foreign_key(&CppInclusion::includee_path).references(&File::path)
                                     ),
                                     orm::make_table("func_decls",
                                                     orm::make_column("id", &FunctionDecl::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &FunctionDecl::function_name),
                                                     orm::make_column("file_path", &FunctionDecl::file_path),
                                                     orm::make_column("return_type", &FunctionDecl::return_type),
                                                     orm::foreign_key(&FunctionDecl::file_path).references(&File::path)
                                     ),
                                     orm::make_table("var_decls",
                                                     orm::make_column("id", &VarDecl::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &VarDecl::name),
                                                     orm::make_column("type", &VarDecl::type),
                                                     orm::make_column("is_global", &VarDecl::is_global),
                                                     orm::make_column("file_path", &VarDecl::file_path),
                                                     orm::foreign_key(&VarDecl::file_path).references(&File::path)
                                     ),
                                     orm::make_table("func_defs",
                                                     orm::make_column("id", &FunctionDef::id, orm::autoincrement(), orm::primary_key()),
                                                     orm::make_column("name", &FunctionDef::function_name),
                                                     orm::make_column("file_path", &FunctionDef::file_path),
                                                     orm::make_column("return_type", &FunctionDef::return_type),
                                                     orm::foreign_key(&FunctionDef::file_path).references(&File::path)
                                     )
    );
    storage.sync_schema(true);
    return storage;
}

using Database = decltype(get_storage(""));

} // namespace oonalysis::db

#endif // DB_H
