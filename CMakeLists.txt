cmake_minimum_required(VERSION 2.8)

project(ram)

set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(src/)

find_package(Boost REQUIRED)
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses REQUIRED)

if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIRS})
        set(BOOST_REGEX_LIB ${Boost_LIBRARY_DIRS}/x86_64-linux-gnu/libboost_regex.so)
endif(Boost_FOUND)

if(CURSES_FOUND)
    set(NCURSES_LIBRARY /usr/lib/x86_64-linux-gnu/libncurses.so)
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
