#include <wx/app.h>
#include "mainframe.h"
#include "oonalysisapp.h"

namespace oonalysis::gui {

bool OOnalysisApp::OnInit() {
    MainFrame* main_frame = new MainFrame(ctx);
    main_frame->Show(true);
    return true;
}

} // namespace oonalysis::gui
