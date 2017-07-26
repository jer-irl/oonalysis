#ifndef DBRECORD_H
#define DBRECORD_H

#include <string>
#include <sqlite3.h>
#include "oonalysis.h"


namespace db {

struct DbRecord {
public:
    DbRecord();
    DbRecord(int id);
    DbRecord get_by_id(int id);

    int id;
    std::string enclosing_file;

protected:
    static std::string tablename;
    static sqlite3_stmt* add_statement;

}; // class DbRecord

} // namespace db

#endif // DBRECORD_H
