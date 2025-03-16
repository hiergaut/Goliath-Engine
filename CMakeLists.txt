project (Goliath-Engine)

cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 14)

if ( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug )
endif()
#project (src)
#set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG -std=c++14 -Wall -pedantic -Wextra -lassimp -O0 -g -Wfatal-errors")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++14 -O3 -Wall -DNDEBUG -lassimp")
#if (CMAKE_BUILD_TYPE STREQUAL "Debug")
#        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra -lassimp -O0 -g -Wfatal-errors")
#endif()

#ADD_CUSTOM_TARGET(debug
#  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Debug ${CMAKE_SOURCE_DIR}
#  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
#  COMMENT "Switch CMAKE_BUILD_TYPE to Debug"
#  )

#ADD_CUSTOM_TARGET(release
#  COMMAND ${CMAKE_COMMAND} -DCMAKE_BUILD_TYPE=Release ${CMAKE_SOURCE_DIR}
#  COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target all
#  COMMENT "Switch CMAKE_BUILD_TYPE to Release"
#  )




find_package(Freetype REQUIRED)

#set(CMAKE_AUTORCC ON)

set (M_SRC_DIR ${PROJECT_SOURCE_DIR}/src/)
set (M_ANIM_TIMELINE_DIR ${PROJECT_SOURCE_DIR}/modules/AnimTimeline/src/)
#set(M_LIB_DIR ${PROJECT_SOURCE_DIR}/lib/)
#set (M_GOLIATH_LIBRARIES)
set (M_Qt5_LIBRARIES Qt5::Core Qt5::Widgets)

#include_directories()
include_directories(
        #    /usr/include/freetype2/
        ${FREETYPE_INCLUDE_DIRS}
        #    .
        ##    ${M_INCLUDE_DIR}
        #    ${CMAKE_CURRENT_BINARY_DIR} #Moc
        ##    ${CMAKE_SOURCE_DIR}/src/
        ##    ${CMAKE_SOURCE_DIR}/src/opengl/
        )


#add_subdirectory(src)
#add_subdirectory(tests)
file(GLOB resources ${PROJECT_SOURCE_DIR}/resources/resources.qrc)
#set (M_RESOURCES_FILE ${PROJECT_SOURCE_DIR}/resources.qrc)
#find_package(Qt5Widgets REQUIRED)
#find_package(Qt5WebEngineWidgets REQUIRED)
#find_package(Qt5WebChannel REQUIRED)
#qt5_add_resources(M_RESOURCES ${PROJECT_SOURCE_DIR}/resources.qrc)
#file (GLOB resources /resources/resources.qrc)

#file(COPY resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
#add_executable(resource.qrc)
#file(COPY assets DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)

#file(GLOB RES_FILES *.vsh *.fsh)
#add_executable(exe_name ${RES_FILES})



add_subdirectory(applications)
add_subdirectory(src)
#add_subdirectory(tests)
#add_subdirectory(resources)

add_subdirectory(modules/AnimTimeline)
add_subdirectory(modules/glm/)

file( COPY ${CMAKE_CURRENT_SOURCE_DIR}/resources DESTINATION ${CMAKE_CURRENT_BINARY_DIR} )

#configure_file(${resources} ${CMAKE_CURRENT_BINARY_DIR}/${resources} COPYONLY)
