cmake_minimum_required(VERSION 3.0)


project (OpenGL)
#project (src)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -lassimp -O0 -g")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#find_package(Qt5 REQUIRED)

find_package(Qt5 COMPONENTS OpenGL REQUIRED)
find_package(OpenGL REQUIRED)

#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

#SET(SimpleProject_SOURCES src/main.cpp src/MainWindow.cpp)
#SET(SimpleProject_FORMS src/MainWindow.ui)
#SET(SimpleProject_HEADERS src/MainWindow.h)
file(GLOB_RECURSE sources *.cpp)
file(GLOB_RECURSE forms *.ui)
file(GLOB_RECURSE headers *.h)


#QT5_WRAP_CPP(${PROJECT_NAME}_HEADERS_MOC ${headers})
#QT5_WRAP_UI(${PROJECT_NAME}_FORMS_HEADERS ${forms})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


include_directories(
    ${M_INCLUDE_DIR}
#    ${CMAKE_SOURCE_DIR}/src/qt/
#    ${CMAKE_SOURCE_DIR}/src/opengl/
    )

#source_group("source files" FILES ${sources})
#source_group("forms files" FILES ${forms})
#source_group("header files" FILES ${headers})

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)
#set(CMAKE_INCLUDE_CURRENT_DIR ON)



add_library(${PROJECT_NAME}
    ${sources}
    ${forms}
    ${headers}
)

#set(path ${CMAKE_SOURCE_DIR}/tests/tillingWindow)
#file(GLOB_RECURSE sources "${path}/*.cpp" "${path}/*.h" "${path}/*.ui")


set(EXT_LIBS Qt5::OpenGL ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${EXT_LIBS})



# add_subdirectory(tests EXCLUDE_FROM_ALL)
