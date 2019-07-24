project (Goliath-Engine)

cmake_minimum_required(VERSION 3.8)
#project (src)

set (M_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/src/)
set (M_GOLIATH_LIBRARIES)

#add_subdirectory(src)
#add_subdirectory(tests)
add_subdirectory(Applications)
add_subdirectory(src)


