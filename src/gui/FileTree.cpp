#include "FileTree.h"

namespace fs = boost::filesystem;

namespace oonalysis::gui {

FileTree::FileTree(std::string root_path, QWidget *parent) : QTreeWidget(parent) {
    this->root_path = root_path;
    redraw();
}

void FileTree::redraw() {
    fs::path root(root_path);

    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(root); iter != end_iter; ++iter) {
        if (fs::is_directory(*iter)) {
            add_dir_item(*iter, nullptr);
        } else {
            add_file_item(*iter, nullptr);
        }
    }
}

void FileTree::add_file_item(const fs::path& path, QTreeWidgetItem *parent) {
    QTreeWidgetItem *item = item_for_path(path, parent);
    if (!parent) {
        addTopLevelItem(item);
    } else {
        parent->addChild(item);
    }
}

void FileTree::add_dir_item(const fs::path& path, QTreeWidgetItem *parent) {
    QTreeWidgetItem *item = item_for_path(path, parent);
    if (!parent) {
        addTopLevelItem(item);
    } else {
        parent->addChild(item);
    }

    fs::directory_iterator end_iter;
    for (fs::directory_iterator iter(path); iter != end_iter; ++iter) {
        if (fs::is_directory(*iter)) {
            add_dir_item((*iter).path(), item);
        } else {
            add_file_item((*iter).path(), item);
        }
    }
}

QTreeWidgetItem *FileTree::item_for_path(const fs::path& path, QTreeWidgetItem *parent) {
    auto res = new QTreeWidgetItem(parent);
    res->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsAutoTristate | Qt::ItemIsEnabled);
    res->setCheckState(0, Qt::Unchecked);
    res->setText(0, QString::fromStdString(path.string()));
    return res;
}

void FileTree::set_root(const std::string& root) {
    root_path = root;
}

std::vector<std::string> FileTree::selected_files() {
    std::vector<std::string> res;

    auto iter = QTreeWidgetItemIterator(this);
    while (*iter) {
        QTreeWidgetItem *item = *iter;
        if (item->checkState(0) && item->childCount() == 0) {
            res.push_back(item->text(0).toStdString());
        }
        ++iter;
    }

    return res;
}

}; // namespace oonalysis::gui