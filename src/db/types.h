#ifndef DB_TYPES_H
#define DB_TYPES_H

#include <string>

namespace oonalysis::db {

struct File {
public:
    int id;
    std::string path;
};

struct CppInclusion {
public:
    int id;
    int includer_id;
    int includee_id;
};

struct FunctionDecl {
public:
    int id;
    std::string function_name;
    int file_id;
    std::string return_type;
};

} // namespace oonalysis::db

#endif // DB_TYPES_H
