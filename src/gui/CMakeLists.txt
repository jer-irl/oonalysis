find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)

find_package(Boost COMPONENTS filesystem REQUIRED)

add_library(gui mainwindow.cpp FileTree.cpp FileNode.cpp Arrow.cpp)
target_link_libraries(gui Qt5::Widgets)
target_link_libraries(gui ${Boost_LIBRARIES})
