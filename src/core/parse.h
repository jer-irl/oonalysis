#ifndef CORE_PARSE_H
#define CORE_PARSE_H

#include <string>
#include <vector>


namespace oonalysis::core {

void universal_parse(const std::vector<std::string>& files);
void parse_files(const std::vector<std::string>& files);

} // namespace oonalysis::core

#endif // CORE_PARSE_H
