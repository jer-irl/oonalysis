#ifndef GUI_OOPROJECT_HPP
#define GUI_OOPROJECT_HPP

#include <string>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/text_oarchive.hpp>

namespace oonalysis::gui {

class OOProject {
public:
    void setProjectPath(std::string projectPath) { this->projectPath = projectPath; }
    std::string getProjectPath(void) { return projectPath; }
    void setRootPath(std::string rootPath) { this->rootPath = rootPath; }
    std::string getRootPath(void) { return rootPath; }
    void setDbPath(std::string dbPath) { this->dbPath = dbPath; }
    std::string getDbPath(void) { return dbPath; }

private:
    std::string projectPath;
    std::string rootPath;
    std::string dbPath;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive& ar, const unsigned int version) {
        ar & projectPath;
        ar & rootPath;
        ar & dbPath;
    }
};

} // namespace oonalysis::gui

#endif // GUI_OOPROJECT_HPP