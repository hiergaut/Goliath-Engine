project (Goliath-Engine)

cmake_minimum_required(VERSION 3.8)
#project (src)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -lassimp -O0 -g -Wfatal-errors")


set (M_SRC_DIR ${PROJECT_SOURCE_DIR}/src/)
#set(M_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
#set (M_GOLIATH_LIBRARIES)
set (M_Qt5_LIBRARIES Qt5::Core Qt5::Widgets Qt5::OpenGL)

#include_directories()

#add_subdirectory(src)
#add_subdirectory(tests)

add_subdirectory(src)
add_subdirectory(applications)
add_subdirectory(tests)


