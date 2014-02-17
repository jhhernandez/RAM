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

typedef unsigned char OPCode;

const OPCode ADD	= 0x20;
const OPCode SUB	= 0x21;
const OPCode MULT	= 0x22;
const OPCode DIV	= 0x23;
const OPCode IMM	= 0x10;
const OPCode DIRECT	= 0x8;
const OPCode INDIRECT	= 0x4;
const OPCode LOAD	= 0x40;
const OPCode STORE	= 0x41;
const OPCode READ	= 0x42;
const OPCode WRITE	= 0x43;
const OPCode JUMP	= 0x81;
const OPCode JGTZ	= 0x82;
const OPCode JZERO	= 0x84;
const OPCode HALT	= 0x00;

typedef std::pair<std::string, Symbol> strSymPair;
typedef std::pair<Symbol, int32_t> symRulePair;

std::string symToString(Symbol);

#endif
