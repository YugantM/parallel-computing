cmake_minimum_required (VERSION 2.8.11)
project (nbody)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# set header files
set(headers 
	include/utils.h)

# set source files
set(sources 
	src/utils.cpp
	src/main.cpp
	)

add_executable(calc 
  ${sources}
  ${headers}
)
 
install(TARGETS nbody DESTINATION bin)
