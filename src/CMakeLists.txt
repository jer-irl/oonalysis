include_directories(.)

find_package (boost COMPONENTS filesystem REQUIRED)
include_directories (${Boost_INCLUDE_DIR})

add_subdirectory (util)
add_subdirectory (db)
add_subdirectory (metrics)
add_subdirectory (core)

# ===========================
# CLI
# ===========================
add_subdirectory (cli)
add_executable (oonalysis-cli cli_main.cc)

target_link_libraries (oonalysis-cli cli)
target_link_libraries (oonalysis-cli util)

# ===========================
# GUI
# ===========================
add_subdirectory (gui)
add_executable (oonalysis-gui gui_main.cc)
target_link_libraries (oonalysis-gui FLTK)
target_link_libraries (oonalysis-gui gui)

# ===========================
# Tests
# ===========================
add_executable (oonalysis-test test_main.cc)
