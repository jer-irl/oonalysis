find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)

find_package(Boost)

add_library(gui mainwindow.cpp FileTree.cpp)
target_link_libraries(gui Qt5::Widgets)
target_link_libraries (gui /usr/local/lib/libboost_filesystem.a)
target_link_libraries (gui /usr/local/lib/libboost_system.a)
