cmake_minimum_required (VERSION 2.8.11)

project (multMatrix LANGUAGES CXX)
add_executable (multMatrix main_multMatrix.cpp multmatrix.cpp multmatrix.h)

project (multMatrixClient LANGUAGES CXX)
add_executable(mainClient main_multMatrix.cpp MultMatrix_cliente.h MultMatrix_cliente.cpp utils.h utils.cpp)
target_link_libraries(mainClient pthread)

project (multMatrixServer LANGUAGES CXX)
add_executable(mainServer mainServer.cpp MultMatrix_server.h MultMatrix_server.cpp utils.h utils.cpp multmatrix.h multmatrix.cpp)
target_link_libraries(mainServer pthread)