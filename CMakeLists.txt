cmake_minimum_required(VERSION 3.28)
project(password_generator_qt)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_PREFIX_PATH "/opt/Qt/6.7.2/gcc_64")

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(password_generator_qt WIN32 src/main.cpp
        src/main-window.cc
        headers/main-window.h
        resources.rc
        src/colored-progressbar.cc
        headers/colored-progressbar.h)
target_link_libraries(password_generator_qt
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
