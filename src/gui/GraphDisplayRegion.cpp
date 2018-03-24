#include "GraphDisplayRegion.hpp"

namespace oonalysis::gui {

QSize GraphDisplayRegion::sizeHint() const {
    int min_x = 0, max_x = 0, min_y = 0, max_y = 0;
    for (QObject* w : children()) {
        auto widget = (QWidget*) w;
        min_x = widget->x() < min_x ? widget->x() : min_x;
        min_y = widget->y() < min_y ? widget->y() : min_y;
        max_x = widget->x() > max_x ? widget->x() : max_x;
        max_y = widget->y() > max_y ? widget->y() : max_y;
    }

    return QSize(max_x - min_x, max_y - min_y);
}

QSize GraphDisplayRegion::minimumSizeHint() const {
    return sizeHint();
}

} // namespace oonalysis::gui