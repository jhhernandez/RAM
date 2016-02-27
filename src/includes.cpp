#include "includes.h"

using namespace std;

string symToString(Symbol sym) {
	string str;

	switch (sym) {
	case Symbol::TS_EOL:
		str = "Symbol::TS_EOL";
		break;

	case Symbol::NTS_S:
		str = "Symbol::NTS_S";
		break;

	case Symbol::NTS_INST:
		str = "Symbol::NTS_INST";
		break;

	case Symbol::TS_MARKER:
		str = "Symbol::TS_MARKER";
		break;

	case Symbol::TS_LABEL:
		str = "Symbol::TS_LABEL";
		break;

	case Symbol::TS_COMMENT:
		str = "Symbol::TS_COMMENT";
		break;

	case Symbol::TS_INST_0:
		str = "Symbol::TS_INST_0";
		break;

	case Symbol::TS_INST_1_LAB:
		str = "Symbol::TS_INST_1_LAB";
		break;

	case Symbol::TS_INST_1_OP:
		str = "Symbol::TS_INST_1_OP";
		break;

	case Symbol::NTS_OPERAND:
		str = "Symbol::NTS_OPERAND";
		break;

	case Symbol::TS_OP_IMM:
		str = "Symbol::TS_OP_IMM";
		break;

	case Symbol::TS_OP_DIRECT:
		str = "Symbol::TS_OP_DIRECT";
		break;

	case Symbol::TS_OP_INDIRECT:
		str = "Symbol::TS_OP_INDIRECT";
		break;
	}

	return str;
}

OPCode operator&(OPCode _code, OPMask _mask)
{
	return static_cast<OPCode>(static_cast<unsigned char>(_code) & static_cast<unsigned char>(_mask));
}

unsigned char operator|(OPCode _a, OPCode _b)
{
	return static_cast<unsigned char>(_a) | static_cast<unsigned char>(_b);
}
