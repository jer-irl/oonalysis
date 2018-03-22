#ifndef GUI_FILETREE_H
#define GUI_FILETREE_H

#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <string>
#include <vector>
#include <boost/filesystem.hpp>

namespace oonalysis::gui {

class FileTreeNode;

class FileTree : public QTreeWidget {
public:
    explicit FileTree(std::string root_path, QWidget *parent = nullptr);

    void set_root(const std::string& root);
    void redraw();

    std::vector<std::string> selected_files();

private:
    std::string root_path;

    void add_file_item(const boost::filesystem::path& path, QTreeWidgetItem *parent);
    void add_dir_item(const boost::filesystem::path& path, QTreeWidgetItem *parent);

    static FileTreeNode *item_for_path(const boost::filesystem::path& path, QTreeWidgetItem *parent);
};

class FileTreeNode : public QTreeWidgetItem {
public:
    using QTreeWidgetItem::QTreeWidgetItem;
    std::string path;
};

} // namespace oonalysis::gui

#endif // GUI_FILETREE_H
