#include "Arrow.hpp"

#include <QPainter>

namespace oonalysis::gui {

Arrow::Arrow(QWidget* pointer, QWidget* pointee, QWidget* parent)
        : QWidget(parent), pointer(pointer), pointee(pointee) {
    resize(abs(pointer->pos().x() - pointee->pos().x()), abs(pointer->pos().y() - pointee->pos().y()));
}

void Arrow::paintEvent(QPaintEvent* event) {
    QWidget::paintEvent(event);

    QPoint head = pointee->pos();
    QPoint tail = pointer->pos();

    QPainter painter(this);
    QPen pen = painter.pen();
    pen.setWidth(3);
    painter.setPen(pen);
    painter.drawLine(QLine(head, tail));
    painter.setBrush(QBrush("red"));
    painter.drawPoint(head);
}

} // namespace oonalysis::gui