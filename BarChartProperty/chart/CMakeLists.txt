set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)


qt_standard_project_setup(REQUIRES 6.8)


qt_add_library(appStairProperty
        STATIC
        src/stair.cpp       inc/stair.hpp
        src/stairchart.cpp  inc/stairchart.hpp
)

qt_add_qml_module(appStairProperty
    URI StairChartProperty
    VERSION 1.0
    QML_FILES
    SOURCES
        src/stair.cpp inc/stair.hpp
        src/stairchart.cpp inc/stairchart.hpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appStairProperty PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appStairProperty
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appStairProperty PUBLIC inc/)
target_link_libraries(appStairProperty 
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
)

set(QML_DIRS "${QML_IMPORT_PATH}")
list(APPEND QML_DIRS "${CMAKE_CURRENT_BINARY_DIR}/chart/")
set(QML_IMPORT_PATH "${QML_DIRS}" CACHE STRING "Chart" FORCE)


include(GNUInstallDirs)
install(TARGETS appStairProperty
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
