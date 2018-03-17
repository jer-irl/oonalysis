find_package(Qt5Widgets)
set(CMAKE_AUTOMOC ON)

add_library(gui mainwindow.cpp)
target_link_libraries(gui Qt5::Widgets)
