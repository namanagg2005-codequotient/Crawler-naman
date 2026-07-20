cmake_minimum_required(VERSION 3.16)

project(Crawler)

set(CMAKE_CXX_STANDARD 17)

find_package(CURL REQUIRED)

add_executable(crawler
    main.cpp
    src/fetcher.cpp
    src/frontier.cpp
)

target_include_directories(crawler PRIVATE
    include
    external/CollectionLibrary/include
)

target_link_libraries(crawler PRIVATE CURL::libcurl)