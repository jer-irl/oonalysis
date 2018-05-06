set(Qt5Widgets_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5Widgets")
find_package(Qt5Widgets REQUIRED)
set(Qt5WebEngine_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5WebEngine")
find_package(Qt5WebEngine REQUIRED)
set(Qt5WebEngineWidgets_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5WebEngineWidgets")
find_package(Qt5WebEngineWidgets REQUIRED)
set(Qt5WebEngineCore_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5WebEngineCore")
find_package(Qt5WebEngineCore REQUIRED)
set(Qt5WebSockets_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5WebSockets")
find_package(Qt5WebSockets REQUIRED)
set(Qt5WebChannel_DIR "/Users/Jeremy/Qt/5.10.1/clang_64/lib/cmake/Qt5WebChannel")
find_package(Qt5WebChannel REQUIRED)

set(CMAKE_AUTOMOC ON)

find_package(Boost COMPONENTS filesystem serialization REQUIRED)

add_library(gui mainwindow.cpp FileTree.cpp FileNode.cpp Arrow.cpp GraphDisplayRegion.cpp ProjectCreationWizard.cpp
        WebSocketTransport.cpp WebSocketClientWrapper.cpp WebInterface.cpp)
target_link_libraries(gui Qt5::Widgets)
target_link_libraries(gui Qt5::WebEngine)
target_link_libraries(gui Qt5::WebEngineWidgets)
target_link_libraries(gui Qt5::WebSockets)
target_link_libraries(gui ${Boost_LIBRARIES})
