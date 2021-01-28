cmake_minimum_required(VERSION 3.19)

# set the project name
project(hash_bench)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(${CMAKE_BINARY_DIR}/conan_paths.cmake)
include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
enable_testing()

add_executable(botan_hash botan_hash/botan_hash.cc )
target_link_libraries(botan_hash PRIVATE ${CONAN_LIBS})

add_executable(openssl_hash openssl_hash/openssl_hash.cc )
target_link_libraries(openssl_hash PRIVATE ${CONAN_LIBS})