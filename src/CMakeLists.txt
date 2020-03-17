set(CMAKE_CXX_STANDARD 17)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_MIN_VERSION "5.14.0")
find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS REQUIRED
        Core
        Network
        Widgets
        Quick
        QuickControls2)

add_executable(drifting-library-desktop
        view/resources.qrc
        model/entrances_model.cpp
        model/library_model.cpp
        model/manga_metadata_model.cpp
        model/manga_content_model.cpp
        model/manga_model.cpp
        model/local/library_model.cpp
        model/local/manga_model.cpp
        model/remote/library_model.cpp
        model/remote/manga_model.cpp
        model/util.cpp
        backend.cpp
        main.cpp)

target_compile_definitions(drifting-library-desktop PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(drifting-library-desktop
        PRIVATE
        Qt5::Core
        Qt5::Network
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2)