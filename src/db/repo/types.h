#ifndef DBTYPES_H
#define DBTYPES_H

#include <string>


namespace oonalysis::db::repo {

typedef struct db_file
{
    int id;
    std::string filename;
    int loc;
} db_file;

typedef struct db_cppinclusion
{
    int id;
    std::string includer;
    std::string includee;
} db_cppinclusion;

typedef struct db_function_decl
{
    int id;
    std::string name;
    std::string file;
} db_function_decl;

} // namespace oonalysis::db::repo

#endif // DBTYPES_H
