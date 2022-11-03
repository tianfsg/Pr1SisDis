
cmake_minimum_required(VERSION 3.5)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXE_LINKER_FLAGS "-static")

project (fileManager LANGUAGES CXX)
add_executable (fileManager main_fm.cpp filemanager.cpp filemanager.h)
target_link_libraries(fileManager pthread)

project(fileManagerClient LANGUAGES CXX)
add_executable(mainClient main_fm.cpp filemanager_stub.h filemanager_stub.cpp utils.h utils.cpp serialize.hpp)
target_link_libraries(mainClient pthread)

project(fileManagerServer LANGUAGES CXX)
add_executable(mainServer mainServer.cpp filemanager_imp.h filemanager_imp.cpp utils.h utils.cpp filemanager.cpp filemanager.h serialize.hpp)
target_link_libraries(mainServer pthread)