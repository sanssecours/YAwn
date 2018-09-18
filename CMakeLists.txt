cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMake)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wsign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=undefined")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=integer")
endif(CMAKE_CXX_COMPILER_ID MATCHES "Clang")

set(SOURCE_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Source)

# ===========
# = Elektra =
# ===========

find_package(Elektra REQUIRED)
include_directories(${ELEKTRA_INCLUDE_DIR})

# ========
# = YAEP =
# ========

find_package(YAEP REQUIRED)

# ========
# = YAwn =
# ========

set(SOURCES_INPUT ${SOURCE_DIRECTORY}/input.hpp ${SOURCE_DIRECTORY}/input.cpp)

if(CMAKE_COMPILER_IS_GNUCXX)
  # Work around error “unrecognized option '--push-state'”
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fuse-ld=gold")

  set_source_files_properties(${SOURCES_INPUT}
                              PROPERTIES
                              COMPILE_FLAGS
                              "-fno-sanitize=undefined")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fvisibility=hidden")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(SOURCE_FILES
    ${SOURCES_INPUT}
    ${SOURCE_DIRECTORY}/token.hpp
    ${SOURCE_DIRECTORY}/token.cpp
    ${SOURCE_DIRECTORY}/lexer.hpp
    ${SOURCE_DIRECTORY}/lexer.cpp
    ${SOURCE_DIRECTORY}/convert.hpp
    ${SOURCE_DIRECTORY}/convert.cpp
    ${SOURCE_DIRECTORY}/yawn.cpp
    ${SOURCE_DIRECTORY}/memory.hpp
    ${SOURCE_DIRECTORY}/memory.cpp
    ${SOURCE_DIRECTORY}/error_listener.hpp
    ${SOURCE_DIRECTORY}/error_listener.cpp
    ${SOURCE_DIRECTORY}/walker.hpp
    ${SOURCE_DIRECTORY}/walker.cpp
    ${SOURCE_DIRECTORY}/objstack.h)

include_directories("${YAEP_INCLUDE_DIRS}")
add_executable(yawn ${SOURCE_FILES})
target_link_libraries(yawn elektra yaep++)
