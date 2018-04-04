#include "mainwindow.hpp"

#include <numeric>
#include <QMenuBar>
#include <QFileDialog>
#include <QDockWidget>
#include <QDesktopWidget>
#include <QInputDialog>
#include <QSettings>
#include <graphviz/gvc.h>
#include <unordered_map>
#include <fstream>
#include <boost/algorithm/string.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "core/parse.h"
#include "graph/inclgraph.h"
#include "graph/callgraph.h"
#include "graph/PlainNode.hpp"
#include "graph/PlainEdge.hpp"
#include "util/compilation.hpp"
#include "FileNode.hpp"
#include "Arrow.hpp"
#include "utils.h"
#include "ProjectCreationWizard.hpp"

namespace fs = boost::filesystem;

namespace oonalysis::gui {

MainWindow* MainWindow::instance = nullptr;

MainWindow::MainWindow() : QMainWindow() {
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

    create_menu_bar();

    file_tree = new FileTree(fs::current_path().string());
    auto left_dock = new QDockWidget("File Selection");
    left_dock->setWidget(file_tree);
    addDockWidget(Qt::LeftDockWidgetArea, left_dock);

    graph_display_region = new GraphDisplayRegion(this);
    setCentralWidget(graph_display_region);

    OOProject proj;
    QSettings settings;
    QStringList l = settings.allKeys();
    std::vector<std::string> list;
    for (QString s : l) {
        list.push_back(s.toStdString());
    }
    std::string projectPath = settings.value("defaultProjectPath", "./newProj.ooproj").toString().toStdString();
    std::ifstream stream(projectPath);
    if (!stream.is_open()) {
        onNewProject();
    } else {
        auto ar = boost::archive::text_iarchive(stream);
        ar >> proj;
        this->project = std::make_shared<OOProject>(proj);
    }
}

void MainWindow::create_menu_bar() {
    QMenuBar *menu_bar = menuBar();

    auto file_menu = new QMenu("File");

    auto newProjectAction = new QAction("New Project...");
    file_menu->addAction(newProjectAction);
    connect(newProjectAction, &QAction::triggered, this, &MainWindow::onNewProject);

    auto openProjectAction = new QAction("Open Project...");
    file_menu->addAction(openProjectAction);
    connect(openProjectAction, &QAction::triggered, this, &MainWindow::onOpenProject);

    auto parse_action = new QAction("Parse files");
    file_menu->addAction(parse_action);
    connect(parse_action, &QAction::triggered, this, &MainWindow::on_parse);

    auto showInclusionsAction = new QAction("Show inclusions");
    file_menu->addAction(showInclusionsAction);
    connect(showInclusionsAction, &QAction::triggered, this, &MainWindow::onShowInclusions);

    menu_bar->addMenu(file_menu);
}

void MainWindow::onNewProject() {
    ProjectCreationWizard wizard;
    wizard.show();
    wizard.exec();
    project = wizard.getCreatedProject();

    QSettings settings;
    settings.setValue("defaultProjectPath", QString::fromStdString(project->getProjectPath()));
    std::ofstream stream(project->getProjectPath());
    auto ar = boost::archive::text_oarchive(stream);
    ar << *project;

    reloadProject();
}

void MainWindow::onOpenProject() {
    std::string projectPath = QFileDialog::getOpenFileName(this).toStdString();

    OOProject proj;
    QSettings settings;
    std::ifstream stream(projectPath);
    auto ar = boost::archive::text_iarchive(stream);
    ar >> proj;
    this->project = std::make_shared<OOProject>(proj);

    settings.setValue("defaultProjectPath", QString::fromStdString(project->getProjectPath()));

    reloadProject();

}

void MainWindow::onShowInclusions() {
    graph_display_region->startInclusionsRendering();
}

void MainWindow::reloadProject() {
    file_tree->set_root(project->getRootPath());
    file_tree->redraw();
    setWindowTitle(QString::fromStdString(project->getProjectPath()));
}

void MainWindow::on_parse() {
    auto files = file_tree->selected_files();
    db::Database db = db::get_storage(project->getDbPath());
    auto args = get_compilation_arguments();
    core::parse_files(db, files, args);
}

MainWindow* MainWindow::get_instance() {
    if (!MainWindow::instance) {
        MainWindow::instance = new MainWindow();
    }
    return MainWindow::instance;
}

std::vector<std::string> MainWindow::get_compilation_arguments() {
    QSettings settings;
    bool ok;
    std::vector<std::string> default_args = util::clang_default_arguments();
    std::string args_line = QInputDialog::getText(
            this,
            QString::fromStdString("Input compilation arguments"),
            QString::fromStdString("Input compilation arguments"),
            QLineEdit::Normal,
            settings.value(
                    QString::fromStdString(std::string("compilation_args")),
                    QString::fromStdString(accumulate(default_args.begin(), default_args.end(), std::string(" ")))
            ).toString(),
            &ok
    ).toStdString();

    if (ok) {
        settings.setValue("compilation_args", QString::fromStdString(args_line));
        settings.sync();
    }

    std::vector<std::string> args;
    boost::split(args, args_line, boost::is_any_of(" \n"));
    return args;
}

} // namespace oonalysis::gui