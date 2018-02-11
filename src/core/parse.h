#ifndef CORE_PARSE_H
#define CORE_PARSE_H

#include <string>
#include <vector>
#include "db/db.h"


namespace oonalysis::core {

void common_parse(const std::vector<std::string>& files);
void parse_files(db::Database& db, const std::vector<std::string>& files);

} // namespace oonalysis::core

#endif // CORE_PARSE_H
