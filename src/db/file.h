#ifndef DB_FILE_H
#define DB_FILE_H

#include <string>

namespace oonalysis::db {

bool add_new_file(const std::string& filename, int* loc);
bool update_loc(const std::string& filename, int loc);
int loc_in_file(const std::string& filename);
uint32_t get_num_files();
float avg_loc();
uint32_t max_loc();

} // namespace oonalysis::db

#endif // DB_FILE_H
