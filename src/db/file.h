#ifndef FILE_H
#define FILE_H

#include <string>
#include <sqlite3.h>
#include "dbrecord.h"


namespace db {

struct File : DbRecord {
public:
    File();
    File(int id);
    void add_to_db();

    std::string filename;

protected:
    static const std::string tablename;
    static sqlite3_stmt* add_statement;
    static sqlite3_stmt* get_statement;

private:
    void init_statics();

}; // class DbRecord

} // namespace db

#endif // DBRECORD_H
