#include <cstdlib>
#include <FL/Fl_Native_File_Chooser.H>
#include <FL/fl_ask.H>
#include "db/init.h"
#include "ctx.h"
#include "menucallbacks.h"
#include "canvas.h"

namespace oonalysis::gui {

void file_open_db(Fl_Widget* w, void* d) {
    if (!w || d) {
        exit(EXIT_FAILURE);
    }

    Fl_Native_File_Chooser chooser;
    chooser.title("Choose database file");
    chooser.directory("~");
    chooser.type(Fl_Native_File_Chooser::BROWSE_FILE);

    switch (chooser.show()) {
    case -1:
        exit(EXIT_FAILURE);
    case 1:
        return;
    default:
        break;
    }

    Ctx* ctx = Ctx::inst();
    ctx->db_filename = chooser.filename();
    db::set_db_name(chooser.filename());
    return;
}

void action_parse(Fl_Widget* w, void* d) {
    if (!w || d) {
        exit(EXIT_FAILURE);
    }

    Ctx* ctx = Ctx::inst();
    if (ctx->db_filename == "") {
        fl_message("No DB selected");
    }
}

void action_visualize(Fl_Widget* w, void* d) {
    if (!w || d) {
        exit(EXIT_FAILURE);
    }

    Ctx* ctx = Ctx::inst();

    ctx->canvas = new Canvas(20, 0, 100, 100);
    ctx->mw.add_resizable(*ctx->canvas);

    ctx->canvas->display();
}

void file_new_db(Fl_Widget* w, void* d);

} // namespace oonalysis::gui
