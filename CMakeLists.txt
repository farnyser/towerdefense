project(lo21)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

set(lo21_SRCS object.cpp enemy.cpp tower.cpp lo21.cpp dock.cpp gamescene.cpp main.cpp)
qt4_automoc(${lo21_SRCS})
add_executable(lo21 ${lo21_SRCS})
target_link_libraries(lo21 ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY})
