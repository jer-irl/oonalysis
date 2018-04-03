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

    image_scroll_area = new QScrollArea(this);
    image_label = new QLabel(image_scroll_area);
    graph_display_region = new GraphDisplayRegion(image_scroll_area);
    setCentralWidget(image_scroll_area);
    image_scroll_area->setWidgetResizable(true);

    OOProject proj;
    QSettings settings;
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

    auto show_inclusions_action = new QAction("Show inclusions");
    file_menu->addAction(show_inclusions_action);
    connect(show_inclusions_action, &QAction::triggered, this, &MainWindow::on_show_inclusions);

    auto show_callgraph_action = new QAction("Show callgraph");
    file_menu->addAction(show_callgraph_action);
    connect(show_callgraph_action, &QAction::triggered, this, &MainWindow::on_show_callgraph);

    auto show_filenode_action = new QAction("Show filenode");
    file_menu->addAction(show_filenode_action);
    connect(show_filenode_action, &QAction::triggered, this, &MainWindow::on_show_filenode);

    auto show_inclusions_rendered_action = new QAction("Show inclusions rendered");
    file_menu->addAction(show_inclusions_rendered_action);
    connect(show_inclusions_rendered_action, &QAction::triggered, this, &MainWindow::on_show_inclusions_rendered);

    menu_bar->addMenu(file_menu);
}

void MainWindow::onNewProject() {
    ProjectCreationWizard wizard;
    wizard.show();
    wizard.exec();
    project = wizard.getCreatedProject();

    QSettings settings;
    settings.setProperty("defaultProjectPath", QString::fromStdString(project->getProjectPath()));
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

    settings.setProperty("defaultProjectPath", QString::fromStdString(project->getProjectPath()));

    reloadProject();

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

void MainWindow::on_show_inclusions() {
    db::Database db = db::get_storage(project->getDbPath());
    auto the_files = file_tree->selected_files();
    Agraph_t *graph = graph::get_inclgraph(db, std::unordered_set<std::string>(the_files.begin(), the_files.end()));
    show_graph_image(graph);
    agclose(graph);
}

void MainWindow::on_show_callgraph() {
    db::Database db = db::get_storage(project->getDbPath());
    auto the_files = file_tree->selected_files();
    Agraph_t* graph = graph::get_callgraph(db, std::unordered_set<std::string>(the_files.begin(), the_files.end()));
    show_graph_image(graph);
    agclose(graph);
}

void MainWindow::show_graph_image(Agraph_t *graph) {
    FILE *image_file = fopen("graph.png", "w");
    GVC_t* gvc = gvContext();
    gvLayout(gvc, graph, "dot");
    gvRender(gvc, graph, "png", image_file);
    fclose(image_file);

    QImage image("graph.png");
    image_label->setPixmap(QPixmap::fromImage(image));
    image_scroll_area->setWidget(image_label);
}

void MainWindow::on_show_filenode() {
    FileNode* node1 = new FileNode("Dummy/path1", this->image_label);
    FileNode* node2 = new FileNode("Dummy/path2", this->image_label);
    node2->move(500, 500);

    auto arrow = new Arrow(node1, node2, this->image_label);
    image_scroll_area->setWidget(this->image_label);

    node1->show();
    node2->show();
    arrow->show();

}

void MainWindow::on_show_inclusions_rendered() {
    db::Database db = db::get_storage(project->getDbPath());
    auto the_files = file_tree->selected_files();
    Agraph_t *graph = graph::get_inclgraph(db, std::unordered_set<std::string>(the_files.begin(), the_files.end()));
    GVC_t* gvc = gvContext();
    gvLayout(gvc, graph, "dot");
    char* xdot_data;
    unsigned int len;
    gvRenderData(gvc, graph, "plain", &xdot_data, &len);

    std::vector<std::string> lines;
    boost::split(lines, xdot_data, boost::is_any_of("\n"));

    // Nodes
    std::unordered_map<std::string, FileNode*> nodes;
    for (const std::string& line : lines) {
        std::vector<std::string> toks;
        boost::split(toks, line, boost::is_any_of(" "));

        if (toks[0] != "node") { continue; }

        graph::PlainNode plain_node(line);

        auto file_node = new FileNode(plain_node.name, this->graph_display_region);
        file_node->move(plain_node.x * PIXELS_PER_INCH, plain_node.y * PIXELS_PER_INCH);
        file_node->show();

        nodes[plain_node.name] = file_node;
    }

    graph_display_region->updateGeometry();

    // Edges
    for (const std::string& line : lines) {
        std::vector<std::string> toks;
        boost::split(toks, line, boost::is_any_of(" "));

        if (toks[0] != "edge") { continue; }

        graph::PlainEdge plain_edge(line);

        auto arrow = new Arrow(nodes[plain_edge.tail], nodes[plain_edge.head], this->graph_display_region);
        arrow->show();
    }

    image_scroll_area->setWidget(graph_display_region);

    agclose(graph);
    gvFreeRenderData(xdot_data);
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