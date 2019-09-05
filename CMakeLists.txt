#####################################
cmake_minimum_required (VERSION 3.0)

project (raspicam-daemon)

list( APPEND CMAKE_CXX_FLAGS "-std=c++11 -DBOOST_LOG_DYN_LINK ${CMAKE_CXX_FLAGS}")

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

FIND_PACKAGE(Threads)
FIND_PACKAGE(raspicam REQUIRED)
FIND_PACKAGE(Boost COMPONENTS system log log_setup REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})

SET(SOURCES
    main.cpp
    Server.cpp
    ConnectionHandler.cpp
    ImageStreamer.cpp
)
SET(HEADERS
    Server.h
    ConnectionHandler.h
    ImageStreamer.h
)

add_executable (raspicam-daemon ${SOURCES})
target_link_libraries(raspicam-daemon ${Boost_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${raspicam_LIBS})

#set (CMAKE_CXX_FLAGS "-g -Wall -DBOOST_LOG_DYN_LINK")
