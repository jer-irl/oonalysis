set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})

add_library(gui oonalysisapp.cc mainframe.cc)

target_link_libraries(gui ${wxWidgets_LIBRARIES})

