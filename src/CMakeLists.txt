add_library(Include SHARED includes.cpp)

add_library(Parser SHARED RAM/Parser.cpp)

add_library(Program SHARED RAM/Program.cpp)

add_library(UI SHARED UI.cpp)

add_library(Tape SHARED RAM/Tape.cpp)

add_library(Registers SHARED RAM/Registers.cpp)

add_library(Machine SHARED RAM/Machine.cpp)

target_link_libraries(Program Include)

target_link_libraries(Machine Registers Tape Program Parser)