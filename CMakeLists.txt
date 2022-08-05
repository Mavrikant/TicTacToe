cmake_minimum_required(VERSION 3.5)

project(TicTacToe VERSION "0.2.2" LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

configure_file (
  "${PROJECT_SOURCE_DIR}/config.h.in"
  "${PROJECT_BINARY_DIR}/config.h"
  )

string(TIMESTAMP BUILD_DATE "%Y-%m-%dT%H:%M:%SZ")
include_directories(${PROJECT_BINARY_BIN})

set(PRE_CONFIGURE_FILE "${PROJECT_SOURCE_DIR}/git.cpp.in")
set(POST_CONFIGURE_FILE "${PROJECT_BINARY_DIR}/git.cpp")

include(git_watcher.cmake)

add_library(git STATIC ${POST_CONFIGURE_FILE})
target_include_directories(git PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
add_dependencies(git check_git)


find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        tictactoecore.cpp
        tictactoecore.h 
        widget.cpp
        widget.h
        widget.ui
        mainwindow.ui
        mainwindow.cpp
        mainwindow.h
        buildinfo.ui
        buildinfo.cpp
        buildinfo.h
        git.h

)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TicTacToe
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TicTacToe APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TicTacToe SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TicTacToe
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TicTacToe PRIVATE Qt${QT_VERSION_MAJOR}::Widgets git)

set_target_properties(TicTacToe PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)
target_compile_definitions(TicTacToe PRIVATE "BUILD_DATE=\"${BUILD_DATE}\"")

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TicTacToe)
endif()


