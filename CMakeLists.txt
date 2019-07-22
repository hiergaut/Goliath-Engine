cmake_minimum_required(VERSION 2.8)
project (Goliath-Engine)

FIND_PACKAGE(Qt5 REQUIRED)
INCLUDE(${QT_USE_FILE})
ADD_DEFINITIONS(${QT_DEFINITIONS})

#SET(SimpleProject_SOURCES src/main.cpp src/MainWindow.cpp)
#SET(SimpleProject_FORMS src/MainWindow.ui)
#SET(SimpleProject_HEADERS src/MainWindow.h)
file(GLOB_RECURSE sources ${CMAKE_SOURCE_DIR}/src/*.cpp)
file(GLOB_RECURSE forms ${CMAKE_SOURCE_DIR}/src/*.ui)
file(GLOB_RECURSE headers ${CMAKE_SOURCE_DIR}/src/*.h)

QT5_WRAP_CPP(${PROJECT_NAME}_HEADERS_MOC ${headers})
QT5_WRAP_UI(${PROJECT_NAME}_FORMS_HEADERS ${forms})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${CMAKE_SOURCE_DIR}/src)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


ADD_EXECUTABLE(${PROJECT_NAME}
    ${sources}
    ${forms}
    ${headers}
)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${EXT_LIBS})
