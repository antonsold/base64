cmake_minimum_required(VERSION 3.12)
project(base64)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(lib/googletest)
include_directories(lib/googletest/googletest/include)
include_directories(lib/googletest/googlemock/include)
add_executable(base64 main.cpp tests/Base64EncoderDecoder.cpp tests/Base64EncoderDecoder.h tests/test.cpp)
target_link_libraries(base64 gtest gtest_main)