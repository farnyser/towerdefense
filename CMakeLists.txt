# Cmake Version
cmake_minimum_required(VERSION 2.6)

# external package
find_package(Qt4 REQUIRED)

# Project configuration.
set(PROJECT_NAME     "Tower Defense")
set(PROJECT_BIN      "lo21")
set(PROJECT_MAIN_DIR ${CMAKE_SOURCE_DIR})
set(PROJECT_DOC_DIR  ${PROJECT_MAIN_DIR}/doc)
set(PROJECT_SRC_DIR  ${PROJECT_MAIN_DIR}/src)
set(PROJECT_INC_DIR  ${PROJECT_MAIN_DIR}/src)

# Set the include directories.
include_directories(${PROJECT_INC_DIR})
include_directories(${QT_INCLUDES})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

# Build a list of sources and moc.
file(GLOB_RECURSE PROJECT_SRC ${PROJECT_SRC_DIR}/*.cpp)
qt4_automoc(${PROJECT_SRC})
qt4_wrap_ui(PROJECT_UIC src/dock.ui)


# Add executable.
add_executable(
	${PROJECT_BIN}
	${PROJECT_SRC}
	${PROJECT_MOC_SRC}
	${PROJECT_UIC}
)

# Configure the linker.
target_link_libraries(
	${PROJECT_BIN}
    ${QT_QTCORE_LIBRARY}
	${QT_QTGUI_LIBRARY}
	${QT_QTOPENGL_LIBRARY}
)

