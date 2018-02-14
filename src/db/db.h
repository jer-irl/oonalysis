#ifndef DB_H
#define DB_H

#include <string>
#include "sqlite_orm/sqlite_orm.h"
#include "types.h"

namespace oonalysis::db {
using Database = sqlite_orm::internal::storage_t<
        sqlite_orm::table_t<
                sqlite_orm::internal::column_t<
                        oonalysis::db::File,
                        int,
                        sqlite_orm::constraints::autoincrement_t,
                        sqlite_orm::constraints::primary_key_t<>
                >,
                sqlite_orm::internal::column_t<
                        oonalysis::db::File,
                        std::__1::basic_string<char>
                >
        >,
        sqlite_orm::table_t<
                sqlite_orm::internal::column_t<
                        oonalysis::db::FunctionDecl,
                        int,
                        sqlite_orm::constraints::autoincrement_t,
                        sqlite_orm::constraints::primary_key_t<>
                >,
                sqlite_orm::internal::column_t<
                        oonalysis::db::FunctionDecl,
                        std::__1::basic_string<char>
                >,
                sqlite_orm::internal::column_t<
                        oonalysis::db::FunctionDecl,
                        int
                >,
                sqlite_orm::internal::column_t<
                        oonalysis::db::FunctionDecl,
                        std::string
                >,
                sqlite_orm::constraints::foreign_key_t<
                        int oonalysis::db::FunctionDecl::*,
                        int oonalysis::db::File::*
                >
        >
>;

Database get_storage(const std::string&);

} // namespace oonalysis::db

#endif // DB_H
