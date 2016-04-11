cmake_minimum_required(VERSION 3.3)
project(testapp)

cmake_policy(SET CMP0015 NEW)
set(OPTIMIZED_BUILD TRUE)

INCLUDE_DIRECTORIES(../../lib)


if (OPTIMIZED_BUILD)
    LINK_DIRECTORIES(../../lib/bin/O3)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O3")
else()
    LINK_DIRECTORIES(../../lib/bin/O0)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -O0")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)

set(OPTIMIZED_BUILD TRUE)

add_executable(testapp ${SOURCE_FILES})

# if boost is avaliable - uncomment
#set(all_libs ccv jpeg png  ${Boost_LIBRARIES})
set(all_libs ccv jpeg png  )


TARGET_LINK_LIBRARIES(testapp ${all_libs} )