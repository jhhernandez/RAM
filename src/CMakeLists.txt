add_library (
	Include
	SHARED
	includes.cpp
)

add_library (
	Parser
	SHARED
	Parser.cpp
)

add_library (
	Program
	SHARED
	Program.cpp
)

target_link_libraries (
	Parser
	Include
)
