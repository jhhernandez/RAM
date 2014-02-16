add_library(
	Tape
	SHARED
	RAM/Tape.cpp
)

add_library(
 	Machine
 	SHARED
 	RAM/Machine.cpp
# 	RAM/Registers.cpp
# 	RAM/ITape.cpp
# 	RAM/OTape.cpp
# 	RAM/Tape.cpp
# 	RAM/Program.cpp
# 	RAM/Parser.cpp
# 	includes.cpp
)

add_library(
	Register
	SHARED
	RAM/Registers.cpp
)

add_library(
	Program
	SHARED
	RAM/Program.cpp
	RAM/Parser.cpp
	includes.cpp
)

add_library(
	Tapes
	SHARED
	RAM/Tape.cpp
	RAM/ITape.cpp
	RAM/OTape.cpp
)

target_link_libraries(
	Machine
	Register
	Tapes
	Program
)

add_library(
	UI
	SHARED
	UI.cpp
)