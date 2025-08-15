set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick QuickControls2)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appBarChartProperty
    src/main.cpp
)

qt_add_qml_module(appBarChartProperty
    URI BarChartProperty
    VERSION 1.0
    QML_FILES
        qml/Main.qml
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appBarChartProperty PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appBarChartProperty
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_include_directories(appBarChartProperty PUBLIC inc/)

target_link_libraries(appBarChartProperty
    PRIVATE
        Qt6::Quick
        Qt6::QuickControls2
        appStairPropertyplugin
)

include(GNUInstallDirs)
install(TARGETS appBarChartProperty
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
