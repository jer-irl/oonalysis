include_directories(.)

find_package (boost COMPONENTS filesystem REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

add_executable (oonalysis-test test_main.cc)
add_executable (oonalysis-cli cli_main.cc)

# ===========================
# Subdirectories
# ===========================
add_subdirectory (util)
add_subdirectory (db)
add_subdirectory (metrics)
add_subdirectory (core)

# ===========================
# Tests
# ===========================
target_link_libraries (oonalysis-test core)

# ===========================
# CLI
# ===========================
add_subdirectory (cli)

target_link_libraries (oonalysis-cli cli)
target_link_libraries (oonalysis-cli util)

# ===========================
# GUI
# ===========================
add_subdirectory (graph)
add_subdirectory (gui)

set(wxWidgets_CONFIGURATION mswu)
find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})
include_directories(${wxWidgets_INCLUDE_DIRS})

add_executable (oonalysis-gui gui_main.cc)
target_link_libraries (oonalysis-gui gui)

