#ifndef GUI_FILETREE_H
#define GUI_FILETREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <string>
#include <boost/filesystem.hpp>

namespace oonalysis::gui {

class FileTree : public QTreeWidget {
public:
    explicit FileTree(std::string root_path, QWidget *parent = nullptr);

    void redraw();

private:
    std::string root_path;

    void add_file_item(const boost::filesystem::path& path, QTreeWidgetItem *parent);
    void add_dir_item(const boost::filesystem::path& path, QTreeWidgetItem *parent);

    static QTreeWidgetItem *item_for_path(const boost::filesystem::path& path, QTreeWidgetItem *parent);
};

} // namespace oonalysis::gui

#endif // GUI_FILETREE_H
