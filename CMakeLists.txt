#header
cmake_minimum_required(VERSION 3.8)
set(TARGET_NAME project_two)
set(QT_MAJOR_VERSION 6)
project(${TARGET_NAME} VERSION 0.0.1 DESCRIPTION "Project Description")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_PREFIX_PATH "C:\\Qt\\6.1.2\\mingw81_64")
set(SOURCE_FILES main.cpp world/tile.h basics/coordinates.h world/terrain_type.h scenes/main_menu.cpp scenes/main_menu.h scenes/main_menu.ui world/map.cpp world/map.h scenes/game_space.cpp scenes/game_space.h scenes/game_space.ui)
add_executable(project_two ${SOURCE_FILES})

#target init
target_compile_options(${TARGET_NAME} PRIVATE -Wall -Wextra -pedantic -Werror)
set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}d" RELEASE_OUTPUT_NAME ${TARGET_NAME})

#find packages
find_package(Qt${QT_MAJOR_VERSION} COMPONENTS Widgets REQUIRED PATHS $ENV{Qt${QT_MAJOR_VERSION}_HOME})
find_package(Qt${QT_MAJOR_VERSION} COMPONENTS Gui REQUIRED PATHS $ENV{Qt${QT_MAJOR_VERSION}_HOME})
find_package(Qt${QT_MAJOR_VERSION} COMPONENTS OpenGLWidgets REQUIRED PATHS $ENV{Qt${QT_MAJOR_VERSION}_HOME})

#link libs
target_link_libraries(Qt${QT_MAJOR_VERSION}::Gui)
target_link_libraries(project_two PRIVATE Qt${QT_MAJOR_VERSION}::Widgets)
target_link_libraries(project_two PRIVATE Qt${QT_MAJOR_VERSION}::OpenGLWidgets)

#include dirs
target_include_directories(${TARGET_NAME} PRIVATE ${Qt${QT_MAJOR_VERSION}_INCLUDE_DIRS})
target_include_directories(${TARGET_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)


