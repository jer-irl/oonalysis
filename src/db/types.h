#ifndef DB_TYPES_H
#define DB_TYPES_H

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

struct FunctionDef {
public:
    int id;
    std::string function_name;
    int file_id;
};

} // namespace oonalysis::db

#endif // DB_TYPES_H