#ifndef STRUTILS_H
#define STRUTILS_H

#include <string>
#include <vector>


namespace oonalysis {

std::string str_join(std::vector<std::string> strings, char glue);
std::vector<std::string> str_split(const std::string& str, const std::string& delim);
char first_nonwhitespace(const std::string& line);
std::string to_lower(const std::string& str);

} // namespace oonalysis

#endif // STRUTILS_H
