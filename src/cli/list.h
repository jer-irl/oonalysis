#ifndef CLI_LIST_H
#define CLI_LIST_H

#include <boost/program_options.hpp>
#include <vector>
#include <string>

using po = boost::program_options;
namespace oonalysis::cli {

void list_main(const std::vector<std::string>>& args);

} // namespace oonalysis::cli

#endif // CLI_LIST_H