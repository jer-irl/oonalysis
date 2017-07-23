#include <string>
#include <vector>

#include "Ctx.h"
#include "OOProg.h"
#include "oonalysis.h"
#include "SrcFile.h"

namespace oonalysis {

Ctx* Ctx::CTX()
{
    static Ctx* CTX = new Ctx();
    return CTX;
}

Ctx::Ctx()
{
    this->Controller = new GuiController();
}

void Ctx::add_file(SrcFile& file)
{
    this->files.push_back(file);
}

void Ctx::add_file(const std::string& filename)
{
    this->files.push_back(SrcFile(filename));
}

OOProg gen_program();

} // namespace oonalysis
