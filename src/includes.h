#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <string>
#include <bits/stl_pair.h>
#include <stdint.h>

enum class Symbol {
        NONE = -1,
	// NON TERMINAL SYMBOLS
        NTS_S = 0,
        NTS_A,
        NTS_B,
        NTS_INST,
        NTS_OPERAND,
	// TERMINAL SYMBOLS
        TS_MARKER,
        TS_LABEL,
        TS_COMMENT,
        TS_INST_0,
        TS_INST_1_LAB,
        TS_INST_1_OP,
        TS_OP_IMM,
        TS_OP_DIRECT,
        TS_OP_INDIRECT,
        TS_TP,
        TS_EOL
};

enum class OPCode: unsigned char {
	HALT		= 0x0,
	INDIRECT	= 0x4, 
	DIRECT		= 0x8,
	IMM		= 0x10,
	ADD		= 0x20,
	SUB		= 0x21,
	MULT		= 0x22,
	DIV		= 0x23,
	LOAD		= 0x40,
	STORE		= 0x41,
	READ		= 0x42,
	WRITE		= 0x43,
	JUMP		= 0x80,
	JGTZ		= 0x81,
	JZERO		= 0x82
};

enum class OPMask: unsigned char {
	TYPE		= 0xE0,
	REDIRECTION	= 0x1C,
	REGISTER	= 0x43,
	OPERATION	= 0x23,
	BRANCH		= 0x87
};

constexpr auto ARITHMETIC = OPCode::ADD;
constexpr auto REGISTER = OPCode::LOAD;
constexpr auto BRANCH = OPCode::JUMP;

std::string symToString(Symbol _sym);

OPCode operator&(OPCode _code, OPMask _mask);
OPCode operator|(OPCode _a, OPCode _b);


#endif
