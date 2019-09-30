cmake_minimum_required(VERSION 3.0)
project (MainApplication)
#project (src)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic -Wextra -lassimp -O0 -g")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin)

#find_package(Qt5 REQUIRED)

#find_package(Qt5 COMPONENTS Core Widgets OpenGL REQUIRED)
#find_package(OpenGL REQUIRED)

#add_definitions(-DGL_SILENCE_DEPRECATION)

#INCLUDE(${QT_USE_FILE})
#ADD_DEFINITIONS(${QT_DEFINITIONS})

#SET(SimpleProject_SOURCES src/main.cpp src/MainWindow.cpp)
#SET(SimpleProject_FORMS src/MainWindow.ui)
#SET(SimpleProject_HEADERS src/MainWindow.h)
file(GLOB_RECURSE sources *.cpp)
#file(GLOB_RECURSE forms *.ui)
#file(GLOB_RECURSE headers *.h)

#file(GLOB_RECURSE so ${M_INCLUDE_DIR}/Gui/TillingWindow/*.cpp)



#QT5_WRAP_CPP(${PROJECT_NAME}_HEADERS_MOC ${headers})
#QT5_WRAP_UI(${PROJECT_NAME}_FORMS_HEADERS ${forms})

#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})


include_directories(
#    .
        ${M_SRC_DIR}
#    ${M_INCLUDE_DIR}
#    ${PROJECT_SOURCE_DIR}/src/
#    ${CMAKE_CURRENT_BINARY_DIR} #Moc
#    ${CMAKE_SOURCE_DIR}/src/
#    ${CMAKE_SOURCE_DIR}/src/opengl/
    )

#add_dependencies(${PROJECT_NAME} Gui)

#source_group("source files" FILES ${sources})
#source_group("forms files" FILES ${forms})
#source_group("header files" FILES ${headers})

#set(CMAKE_AUTOMOC ON)
#set(CMAKE_AUTORCC ON)
#set(CMAKE_AUTOUIC ON)

#set(CMAKE_INCLUDE_CURRENT_DIR ON)

#file (GLOB resources ${M_RESOURCES_FILE})


add_executable(${PROJECT_NAME}
    ${sources}
#    ${forms}
#    ${headers}
#    ${resources}
#        ${M_RESOURCES}
#    ${so}
)

#set(path ${CMAKE_SOURCE_DIR}/tests/tillingWindow)
#file(GLOB_RECURSE sources "${path}/*.cpp" "${path}/*.h" "${path}/*.ui")

#target_include_directories(${PROJECT_NAME} ${M_INCLUDE_DIR})


#set(EXT_LIBS Qt5::OpenGL ${OPENGL_LIBRARIES})
target_link_libraries(${PROJECT_NAME} src)
#target_link_libraries(${PROJECT_NAME} ${M_Qt5_LIBRARIES} Qt5::OpenGL src)

#add_dependencies(${PROJECT_NAME} src)



# add_subdirectory(tests EXCLUDE_FROM_ALL)
