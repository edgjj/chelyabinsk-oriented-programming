cmake_minimum_required (VERSION 3.10)

project (chelyabinsk-oriented-programming VERSION 0.01)

file (GLOB_RECURSE SRC "include/*.h" "src/*.c")

set (CMAKE_C_FLAGS "-Wall -Wextra -O2")
set (CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -DCOP_DBG")
add_executable (cop ${SRC})
