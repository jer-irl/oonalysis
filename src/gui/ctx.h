#ifndef GUI_CTX_H
#define GUI_CTX_H

#include <string>

namespace oonalysis::gui {

class Ctx {
public:
    static Ctx* inst();

    std::string db_filename;



}; // class Ctx

} // namespace oonalysis::gui

#endif // GUI_CTX_H
