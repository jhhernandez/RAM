#include "includes.h"

using namespace std;

string symToString(Symbol sym) {
	string str;

	switch (sym) {
	case NONE:
        str = "";
		break;

	case NTS_S:
		str = "NTS_S";
		break;

	case NTS_INST:
		str = "NTS_INST";
		break;

	case TS_MARKER:
		str = "TS_MARKER";
		break;

	case TS_LABEL:
		str = "TS_LABEL";
		break;

	case TS_COMMENT:
		str = "TS_COMMENT";
		break;

	case TS_INST_0:
		str = "TS_INST_0";
		break;

	case TS_INST_1_LAB:
		str = "TS_INST_1_LAB";
		break;

	case TS_INST_1_OP:
		str = "TS_INST_1_OP";
		break;

	case NTS_OPERAND:
		str = "NTS_OPERAND";
		break;

	case TS_OP_IMM:
		str = "TS_OP_IMM";
		break;

	case TS_OP_DIRECT:
		str = "TS_OP_DIRECT";
		break;

	case TS_OP_INDIRECT:
		str = "TS_OP_INDIRECT";
		break;
	}

	return str;
}
