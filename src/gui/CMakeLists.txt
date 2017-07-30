add_library (gui guicontroller.cc MainToolbar.cc MainWindow.cc opendialog.cc)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(Qt5_DIR ~/Qt/5.9.1/clang_64/lib/cmake/Qt5)
find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories (~/Qt/5.9.1/clang_64/include)
target_link_libraries(gui Qt5::Widgets Qt5::Core Qt5::Gui)
