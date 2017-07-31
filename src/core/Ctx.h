#ifndef CTX_H
#define CTX_H

#include <vector>
#include "SrcFile.h"
#include "OOProg.h"


namespace oonalysis {
namespace core {

class Ctx
{
public:
    static Ctx* CTX();

    Ctx();

    OOProg gen_program();

private:
    void add_file(SrcFile& file);

    void add_file(const std::string& filename);

    std::vector<SrcFile> files;
}; // class Ctx

Ctx& CTX();

} // namespace core
} // namespace oonalysis

#endif // CTX_H
