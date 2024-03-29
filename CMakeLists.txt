cmake_minimum_required(VERSION 3.25)

project(RVC)

set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wno-deprecated-declarations")

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugAddress")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=address")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugLeak")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=leak")
elseif (CMAKE_BUILD_TYPE STREQUAL "DebugMemory")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -fsanitize=memory")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
	set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O3")
endif ()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_HOME_DIRECTORY}/bin)

file(GLOB RVC_SOURCES
	src/main.c
	src/init.c
	src/add.c
	src/commit.c
	src/error_handling.c
	src/utils.c)

find_package(OpenSSL REQUIRED)
find_package(ZLIB REQUIRED)
include(cmake/FetchCMocka.cmake)

add_subdirectory(tests)

add_executable(rvc ${RVC_SOURCES})
target_link_libraries(rvc OpenSSL::SSL ZLIB::ZLIB)
target_include_directories(rvc PRIVATE ${CMAKE_HOME_DIRECTORY}/include)
