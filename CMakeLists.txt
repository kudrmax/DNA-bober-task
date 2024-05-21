cmake_minimum_required(VERSION 3.26)
project(DNA)

set(CMAKE_CXX_STANDARD 17)

FIND_PACKAGE( Boost 1.40 COMPONENTS program_options REQUIRED )
INCLUDE_DIRECTORIES( ${Boost_INCLUDE_DIR} )

file(GLOB_RECURSE my_src source/*.cpp)
add_executable(DNA ${my_src})

TARGET_LINK_LIBRARIES(DNA LINK_PUBLIC ${Boost_LIBRARIES} )
