set (MACHINE_SOURCES
	includes.cpp
 	RAM/Machine.cpp
 	RAM/Tape.cpp
	RAM/Registers.cpp
	RAM/Program.cpp
	RAM/Parser.cpp
	RAM/Tape.cpp
	RAM/ITape.cpp
	RAM/OTape.cpp
)

add_library(
 	Machine
 	SHARED
 	${MACHINE_SOURCES}
)

add_library(
	UI
	SHARED
	UI.cpp
)