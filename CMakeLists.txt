cmake_minimum_required(VERSION 3.5)

project(Sha3_Keccak LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


add_executable(main main.c)

target_link_libraries(main PRIVATE akrypt-shared)

target_include_directories(main PRIVATE ${CMAKE_CURRENT_LIST_DIR}/libakrypt-0.x/source)