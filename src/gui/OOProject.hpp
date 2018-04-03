#ifndef GUI_OOPROJECT_HPP
#define GUI_OOPROJECT_HPP

#include <string>

namespace oonalysis::gui {

class OOProject {
public:
    void setProjectPath(std::string projectPath) { projectPath = projectPath; }
    std::string getProjectPath(void) { return projectPath; }
    void setRootPath(std::string rootPath) { rootPath = rootPath; }
    std::string getRootPath(void) { return rootPath; }
    void setDbPath(std::string dbPath) { dbPath = dbPath; }
    std::string getDbPath(void) { return dbPath; }

private:
    std::string projectPath;
    std::string rootPath;
    std::string dbPath;
};

} // namespace oonalysis::gui

#endif // GUI_OOPROJECT_HPP