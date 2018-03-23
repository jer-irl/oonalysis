#ifndef GUI_FILENODE_HPP
#define GUI_FILENODE_HPP

#include <QFrame>

namespace oonalysis::gui {

class FileNode : public QFrame {
public:
    explicit FileNode(const std::string& path, QWidget* parent = nullptr);
    virtual QSize sizeHint() const override;

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    std::string path;
};

} // namespace oonalysis::gui

#endif // GUI_FILENODE_HPP