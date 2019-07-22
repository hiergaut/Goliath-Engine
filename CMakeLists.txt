cmake_minimum_required(VERSION 3.1.0)
project (Goliath-Engine)

set(CMAKE_CXX_FLAGS '${CMAKE_CXX_FLAGS} "-std=c++11 -Wall -pedantic -Wextra -lassimp")

# file(GLOB_RECURSE data resources/*)


# ------------------------------ LIBRARY
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
#find_package(Qt5Widgets)
#find_package(QT5OpenGL)
find_package(Qt5 REQUIRED COMPONENTS Widgets Core)

find_package(OpenGL REQUIRED)



# ------------------------------ EXECUTABLE
file(GLOB_RECURSE sources src/*)
add_executable(${PROJECT_NAME} ${sources})
#qt5_use_modules(${PROJECT_NAME} Widgets OpenGL)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${QT_LIBRARIES} ${OPENGL_LIBRARIES})

#set(EXECUTABLE_OUTPUT_PATH bin/${CMAKE_BUILD_TYPE})

# target_compile_options(MainWindow PUBLIC -std=c++1y -Wall -Wfloat-conversion)

# file(COPY ${data} DESTINATION resources)
