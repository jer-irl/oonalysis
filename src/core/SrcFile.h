#ifndef SRCFILE_H
#define SRCFILE_H

#include <string>
#include <fstream>
#include "SrcObj.h"


namespace oonalysis {
namespace core {

class SrcFile : public SrcObj
{
public:
    SrcFile(const std::string& filename);
    std::string get_text() const;
    std::string present_name() const;
private:
    std::filebuf* get_file();
    std::string filename;
}; // class SrcFile

} // namespace core
} // namespace oonalysis

#endif // SRCFILE_H
