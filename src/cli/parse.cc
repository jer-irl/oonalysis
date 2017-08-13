#include <vector>
#include <string>
#include <exception>
#include <tuple>
#include <boost/filesystem.hpp>
#include "parse.h"
#include "core/parse.h"
#include "db/init.h"
extern "C" {
#include "util/log.h"
}

namespace fs = boost::filesystem;
namespace {

static std::vector<std::string> glob(const std::string& filename)
{
    LOG(TRACE, "Globbing filenames");
    std::vector<std::string> res;
    fs::path p = filename;

    if (fs::is_regular_file(p)) {
        res.push_back(p.native());
        return res;
    }

    for (auto iter : fs::recursive_directory_iterator(p)) {
        if (fs::is_regular_file(iter)) {
            res.push_back(iter.path().native());
        }
    }

    return res;
}

} // anon namespace

namespace oonalysis {
namespace cli {

subcmd_t determine_cmd(const std::vector<std::string>& args)
{
    LOG(DEBUG, "Determining subcommand");

    if (args.size() == 1) {
        LOG(ERROR, "Subcommand required");
        throw std::invalid_argument("No subcommand");
    }

    const std::string cmd = args[1];
    if (cmd == "parse") {
        return PARSE;
    } else if (cmd == "show") {
        return SHOW;
    } else if (cmd == "analyze") {
        return ANALYZE;
    } else if (cmd == "") {
        LOG(ERROR, "Subcommand required");
        throw std::invalid_argument("No subcommand");
    } else {
        throw std::invalid_argument("bad subcommand");
    }
}

void dispatch_cmd(subcmd_t cmd, const std::vector<std::string>& args)
{
    switch (cmd) {
    case PARSE:
        dispatch_parse(args);
        break;
    case SHOW:
    case ANALYZE:
    default:
        throw std::invalid_argument("bad subcommand");
        break;
    }
}

void dispatch_parse(const std::vector<std::string>& args)
{
    LOG(TRACE, "Dispatching parse");

    std::vector<std::string> filenames;
    std::string output = "tmp.db";
    for (auto iter = args.begin() + 2; iter != args.end(); iter++) {
        // Output option
        if (*iter == "-o") {
            iter++;
            output = *iter;
            continue;
        }

        // Positional filenames
        std::vector<std::string> globbed = glob(*iter);
        filenames.insert(filenames.end(), globbed.begin(), globbed.end());
    }

    db::set_db_name(output);
    db::init_db();
    core::parse_files(filenames);
}

} // namespace cli
} // namespace oonalysis

