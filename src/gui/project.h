//
// Created by Jeremy Schroeder on 2/1/18.
//

#ifndef OONALYSIS_PROJECT_H
#define OONALYSIS_PROJECT_H

#include <vector>
#include <boost/filesystem.hpp>

namespace fs = boost::filesystem;
namespace oonalysis::gui {

class Project {
public:
    Project(fs::path path);
    void write_out();
    void read_in();

private:
    fs::path path;
    fs::path root;
    std::vector<fs::path> files;
};


} // namespace oonalysis::gui
#endif //OONALYSIS_PROJECT_H
