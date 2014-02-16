#ifndef INCLUDES_H_
#define INCLUDES_H_

#include <string>
#include <bits/stl_pair.h>
#include <stdint.h>

enum Symbol {
		NONE = -1,
        NTS_S = 0,
		NTS_A,
		NTS_B,
        NTS_INST,
        NTS_OPERAND,
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

typedef unsigned char opCode;

enum Op {
        LOAD    = 0x1001,
        STORE   = 0x1010,
        READ    = 0x1100,
        WRITE   = 0x1011,
        ADD     = 0x100,
        SUB     = 0x101,
        MULT    = 0x110,
        DIV     = 0x111,
        JUMP    = 0x10001,
        JGTZ    = 0x10010,
        JZERO   = 0x10100,
        HALT    = 0x11111111
};

typedef std::pair<std::string, Symbol> strSymPair;
typedef std::pair<Symbol, int32_t> symRulePair;

std::string symToString(Symbol);

#endif
