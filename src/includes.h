#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <string>
#include <bits/stl_pair.h>
#include <stdint.h>

enum class Symbol: char {
        NONE = -1,
		// NON TERMINAL SYMBOLS
        NTS_S = 0, //< PROGRAM STARTING RULE
        NTS_A,	//< PROGRAM RULE A
        NTS_B,	//< PROGRAM RULE B
        NTS_INST,	// INSTRUCTION
        NTS_OPERAND,	// OPERAND
		// TERMINAL SYMBOLS
        TS_MARKER,	//
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

//typedef unsigned char OPCode;

enum OPCode {
	HALT = 0x0,
	INDIRECT = 0x4, 
	DIRECT = 0x8,
	IMM = 0x10,
	ADD = 0x20,
	SUB = 0x21,
	MULT = 0x22,
	DIV = 0x23,
	LOAD = 0x40,
	STORE = 0x41,
	READ = 0x42,
	WRITE = 0x43,
	JUMP = 0x80,
	JGTZ = 0x81,
	JZERO = 0x82
};

typedef std::pair<std::string, Symbol> strSymPair;
typedef std::pair<Symbol, int32_t> symRulePair;

const std::string& symToString(Symbol);

#endif
