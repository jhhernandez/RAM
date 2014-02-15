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

enum Op {
        LOAD,
        STORE,
        READ,
        WRITE,
        ADD,
        SUB,
        MULT,
        DIV,
        JUMP,
        JGTZ,
        JZERO,
        HALT
};

typedef std::pair<std::string, Symbol> strSymPair;
typedef std::pair<Symbol, int32_t> symRulePair;

std::string symToString(Symbol);

#endif
