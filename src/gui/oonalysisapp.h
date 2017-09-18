#ifndef GUI_OONALYSISAPP_H
#define GUI_OONALYSISAPP_H

#include <wx/app.h>

namespace oonalysis::gui {

class OOnalysisApp : public wxApp {
public:
    virtual bool OnInit();
};

} // namespace oonalysis::gui

#endif // GUI_OONALYSISAPP_H
