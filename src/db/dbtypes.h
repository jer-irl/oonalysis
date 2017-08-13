#ifndef DBTYPES_H
#define DBTYPES_H

#include <string>


namespace oonalysis::db {

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

} // namespace oonalysis::db

#endif // DBTYPES_H
