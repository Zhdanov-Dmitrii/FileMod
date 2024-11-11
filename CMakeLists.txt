cmake_minimum_required(VERSION 3.16)

project(FileMod VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appFileMod
    main.cpp
)

qt_add_qml_module(appFileMod
    URI FileMod
    VERSION 1.0
    QML_FILES
        Main.qml
        SOURCES
        SOURCES filewriterprocessor.h filewriterprocessor.cpp
        SOURCES ifileprocessor.h
        SOURCES filemodifierprocessor.h filemodifierprocessor.cpp
        SOURCES filewriterwithcounter.h filewriterwithcounter.cpp
        SOURCES filefilter.h filefilter.cpp
        SOURCES common.h
        SOURCES fileprocessorfactory.h fileprocessorfactory.cpp
        SOURCES filemanager.h filemanager.cpp
        SOURCES controller.h controller.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appFileMod PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appFileMod
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appFileMod
    PRIVATE Qt6::Quick
    PRIVATE Qt6::Widgets
)

include(GNUInstallDirs)
install(TARGETS appFileMod
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
