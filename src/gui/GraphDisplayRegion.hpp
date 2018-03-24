#ifndef GUI_GRAPHDISPLAYREGION_HPP
#define GUI_GRAPHDISPLAYREGION_HPP

#include <QWidget>

namespace oonalysis::gui {

class GraphDisplayRegion : public QWidget {
public:
    using QWidget::QWidget;

    virtual QSize sizeHint() const override;
    virtual QSize minimumSizeHint() const override;
};

} // namespace oonalysis::gui

#endif // GUI_GRAPHDISPLAYREGION_HPP