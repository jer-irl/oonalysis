#include "FileNode.hpp"

#include <QPainter>
#include <QLabel>

namespace oonalysis::gui {

FileNode::FileNode(const std::string& path, QWidget* parent) : QFrame(parent, Qt::Widget), path(path) {
    QLabel* label = new QLabel(QString::fromStdString(path), this);
    setFrameShape(QFrame::Box);
    setLineWidth(2);
}

void FileNode::paintEvent(QPaintEvent *event) {
    QFrame::paintEvent(event);
}

QSize FileNode::sizeHint() const {
    return QSize(100, 100);
}

} // namespace oonalysis::gui