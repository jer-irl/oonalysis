#include "FileNode.hpp"

#include <QPainter>

namespace oonalysis::gui {

FileNode::FileNode(const std::string& path, QWidget* parent) : QFrame(parent, Qt::Widget), path(path) {
    label = std::make_unique<QLabel>(QString::fromStdString(path), this);
    setFrameShape(QFrame::Box);
    setLineWidth(2);
}

void FileNode::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
}

} // namespace oonalysis::gui