set(CMAKE_CXX_STANDARD 14)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(QT_MIN_VERSION "5.14.0")
find_package(Qt5 ${QT_MIN_VERSION} COMPONENTS REQUIRED
        Core
        Widgets
        Quick
        QuickControls2)

add_executable(drifting_library_desktop
        view/resources.qrc
        view_model/manga_list_view_model.cpp
        view_model/manga_detail_view_model.cpp
        view_model/manga_reader_view_model.cpp
        backend.cpp
        main.cpp)

target_compile_definitions(drifting_library_desktop PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)

target_link_libraries(drifting_library_desktop
        PRIVATE
        Qt5::Core
        Qt5::Widgets
        Qt5::Quick
        Qt5::QuickControls2)