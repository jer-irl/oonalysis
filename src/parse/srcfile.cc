#include <fstream>
#include "SrcFile.h"

namespace oonalysis {

SrcFile::SrcFile(const std::string& filename)
{
    this->filename = filename;
    return;
}

std::filebuf* SrcFile::get_file()
{
    std::filebuf* res = new std::filebuf();
    res->open(this->filename, std::ios_base::in);
    return res;
}

std::string SrcFile::present_name() const
{
    return this->filename;
}


} // namespace oonalysis
