cmake_minimum_required(VERSION 3.5)

project(geco LANGUAGES CXX)

set(MAIN_EXE ${CMAKE_PROJECT_NAME})
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Libraries
find_package (LibXml2 REQUIRED)
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${LIBXML2_INCLUDE_DIR})

# Source files
file(GLOB SOURCES
    "*.cpp"
    "dbase/*.cpp"
    )

# Build
add_executable(${MAIN_EXE} ${SOURCES})
target_link_libraries(${MAIN_EXE} ${LIBXML2_LIBRARIES})
