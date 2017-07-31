#include <map>
#include <vector>
#include <string>
#include "oonalysis.h"
#include "strutils.h"

namespace oonalysis {
namespace core {

std::string file_ext(const std::string& filename)
{
    std::vector<std::string> toks = str_split(filename, ".");
    return toks.back();
}

Lang lang_from_filename(const std::string& filename)
{
    std::string ext = to_lower(file_ext(filename));

    // Obvious
    if (ext == "c")    { return C; }
    if (ext == "cc"
     || ext == "cpp")  { return CPP; }
    if (ext == "hs")   { return HS; }
    if (ext == "java") { return OTHER; }
    if (ext == "py")   { return PY; }

    // Not Obvious
    if (ext == "makefile"
     || ext == "so"
     || ext == "dll"
     || ext == "o"
     || ext == "gitignore") { return NONE; }

    // Non-Code
    if (ext == "doc"
     || ext == "docx"
     || ext == "txt"
     || ext == "md"
     || ext == "markdown"
     || ext == "yml"
     || ext == "xml"
     || ext == "yaml") { return NONE; }

    // TODO make warning
    return UNKNOWN;
}

Lang lang_from_filenames(const std::vector<std::string>& filenames)
{
    std::map<Lang, int> score;
    score[C]   = 0;
    score[CPP] = 0;
    score[HS]  = 0;
    score[PY]  = 0;

    for (std::string filename : filenames) {
        score[lang_from_filename(filename)]++;
    }

    Lang res = NONE;
    int max_count = 0;
    for (auto it = score.begin(); it != score.end(); ++it) {
        if (it->second > max_count) {
            max_count = it->second;
            res = it->first;
        }
    }

    return res;
}

} // namespace core
} // namespace oonalysis
