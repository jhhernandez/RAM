cmake_minimum_required(VERSION 2.8)

# set(CMAKE_C_COMPILER /usr/bin/clang)
# set(CMAKE_CXX_COMPILER /usr/bin/clang++)

project(ram)

set(CMAKE_BUILD_TYPE DEBUG)
list(APPEND CMAKE_CXX_FLAGS "-std=c++14")

include_directories(src/)
include_directories(src/RAM)
add_subdirectory(src/)

find_package(Boost REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
		find_library(
			BOOST_REGEX_LIB
			libboost_regex.so
			PATHS ${Boost_LIBRARY_DIRS}
		)
endif(Boost_FOUND)

if(CURSES_FOUND)
	find_library(
		NCURSES_LIBRARY
		libncurses.so
	)
endif(CURSES_FOUND)

add_executable(ram main.cpp)

target_link_libraries(
	ram
	${BOOST_REGEX_LIB}
	Machine
	${NCURSES_LIBRARY}
	UI
)

install(TARGETS ram RUNTIME DESTINATION bin)
