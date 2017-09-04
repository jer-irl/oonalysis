#ifndef GUI_GUINODE_H
#define GUI_GUINODE_H

#include <FL/Fl_Box.H>
#include "graph/node.h"

namespace oonalysis::gui {

class GuiNode : public graph::Node, public Fl_Box {
public:
    GuiNode();

}; // class GuiNode

class FileNode : public GuiNode {
}; // class FileNode

class ImplFileNode : public FileNode {
}; // class ImplFileNode

class DeclFileNode : public FileNode {
}; // class DeclFileNode

} // namespace oonalysis::gui

#endif // GUI_GUINODE_H
