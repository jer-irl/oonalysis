#ifndef SRCOBJ_H
#define SRCOBJ_H

#include <vector>
#include <string>
#include "oonalysis.h"


namespace oonalysis {

class SrcObj
{
public:
    void add_child(SrcObj& child);
    std::string present_name() const;
private:
    std::string declared_file;
    std::string defined_file;
    std::vector<SrcObj> children;
}; // class SrcObj

} // namespace oonalysis

#endif // SRCOBJ_H
