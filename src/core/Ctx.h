#ifndef CTX_H
#define CTX_H

#include <vector>
#include "OOProg.h"


namespace oonalysis::core {

class Ctx
{
public:
    static Ctx* CTX();

    Ctx();

    OOProg gen_program();

private:
    void add_file(const std::string& filename);
}; // class Ctx

Ctx& CTX();

} // namespace oonalysis::core

#endif // CTX_H
