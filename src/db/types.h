#ifndef DB_TYPES_H
#define DB_TYPES_H

#include <string>

namespace oonalysis::db {

struct File {
public:
    std::string path;
};

struct CppInclusion {
public:
    std::string includer_path;
    std::string includee_path;
};

struct FunctionDecl {
public:
    int id;
    std::string function_name;
    std::string file_path;
    std::string return_type;
};

struct FunctionDef {
public:
    int id;
    std::string function_name;
    std::string file_path;
    std::string return_type;
};

struct VarDecl {
public:
    int id;
    std::string name;
    std::string type;
    int is_global;
    std::string file_path;
};

} // namespace oonalysis::db

#endif // DB_TYPES_H
