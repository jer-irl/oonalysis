#ifndef DB_FILE_H
#define DB_FILE_H

#include <string>

namespace oonalysis::db {

bool add_new_file(const std::string& filename, int* loc);
bool update_loc(const std::string& filename, int loc);
int loc_in_file(const std::string& filename);
int get_num_files();

} // namespace oonalysis::db

#endif // DB_FILE_H
