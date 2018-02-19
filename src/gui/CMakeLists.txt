set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED COMPONENTS core base webview)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})

add_library(gui oonalysisapp.cc mainframe.cc project.cpp project.h)
target_link_libraries(gui ${wxWidgets_LIBRARIES})
