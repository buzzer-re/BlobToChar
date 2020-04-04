cmake_minimum_required(VERSION 3.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Grant that this project will work in early cmake versions
if (${CMAKE_VERSION} VERSION_LESS 3.1)
    cmake_policy(VERSION ${CMAKE_MAJOR_VERSION}.${CMAKE_MINOR_VERSION})
endif()


project(PayloadToChar VERSION 1.0 DESCRIPTION "Transform your blob into an simple char array")

add_library(FileManager src/FileManager.cpp)
add_library(ArgParser src/Argparse.cpp)

add_executable(app src/main.cpp)
target_link_libraries(app PUBLIC FileManager)
target_link_libraries(app PUBLIC ArgParser)
