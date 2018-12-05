cmake_minimum_required(VERSION 2.8)

project(SharedMem)
set(Boost_USE_STATIC_LIBS OFF)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.68.0 COMPONENTS system)

message("Hello ${Boost_VERSION}!")       # Substitute a variable into the message

if(Boost_FOUND)
    add_executable(${PROJECT_NAME} "main.cpp")
    #add_library("helper" "helper.h")
    #add_library("msgqr" "msgQ_Rec.c")
    #add_library("msgqs" "msgQ_Send.c")
    target_link_libraries(${PROJECT_NAME} ${Boost_FILESYSTEM_LIBRARY} ${Boost_SYSTEM_LIBRARY})
endif()

