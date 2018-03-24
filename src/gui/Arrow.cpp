#include "Arrow.hpp"

#include <QPainter>

namespace oonalysis::gui {

Arrow::Arrow(QWidget* pointer, QWidget* pointee, QWidget* parent)
        : QWidget(parent), pointer(pointer), pointee(pointee) {
    resize(abs(pointer->pos().x() - pointee->pos().x()), abs(pointer->pos().y() - pointee->pos().y()));
    int x = pointer->x() < pointee->x() ? pointer->x() : pointee->x();
    int y = pointer->y() < pointee->y() ? pointer->y() : pointee->y();
    move(x, y);
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

QSize Arrow::sizeHint() const {
    return QSize(abs(pointee->x() - pointer->x()), abs(pointee->y() - pointer->y()));
}

} // namespace oonalysis::gui