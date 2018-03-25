#ifndef CORE_PARSE_H
#define CORE_PARSE_H

#include <string>
#include <vector>
#include "db/db.h"


namespace oonalysis::core {

void parse_files(db::Database& db, const std::vector<std::string>& files, const std::vector<std::string>& args);
void parse_file(db::Database& db, const std::string& file, const std::vector<std::string>& args);

} // namespace oonalysis::core

#endif // CORE_PARSE_H
