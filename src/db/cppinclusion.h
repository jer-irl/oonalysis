#ifndef DB_CPPINCLUSION_H
#define DB_CPPINCLUSION_H

#include <string>
#include <vector>

namespace oonalysis::db {

bool add_new_inclusion(const std::string& includer, const std::string& includee);
std::vector<std::string> get_inclusions_in_file(const std::string& filename);
std::vector<std::string> get_inclusions_of_file(const std::string& filename);

} // namespace oonalysis::db

#endif // DB_CPPINCLUSION_H
