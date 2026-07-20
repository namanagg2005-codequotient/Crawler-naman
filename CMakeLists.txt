cmake_minimum_required(VERSION 3.16)

project(CodeQuotientProject2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

find_package(CURL REQUIRED)

add_executable(crawler
    main.cpp
    src/fetcher.cpp
    src/frontier.cpp
)

target_link_libraries(crawler PRIVATE CURL::libcurl)