#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <string>
#include <bits/stl_pair.h>
#include <stdint.h>

enum Symbol {
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

typedef unsigned char OPCode;

const OPCode INDIRECT	= 0x4;	// 4
const OPCode DIRECT	= 0x8;	// 8
const OPCode IMM	= 0x10;	// 16
const OPCode ADD	= 0x20;	// 32
const OPCode SUB	= 0x21;	// 33
const OPCode MULT	= 0x22;	// 34
const OPCode DIV	= 0x23;	// 35
const OPCode LOAD	= 0x40;	// 64
const OPCode STORE	= 0x41;	// 65
const OPCode READ	= 0x42;	// 66
const OPCode WRITE	= 0x43;	// 67
const OPCode JUMP	= 0x81;	// 129
const OPCode JGTZ	= 0x82;	// 130
const OPCode JZERO	= 0x84;	// 132
const OPCode HALT	= 0x00;

typedef std::pair<std::string, Symbol> strSymPair;
typedef std::pair<Symbol, int32_t> symRulePair;

std::string symToString(Symbol);

#endif
