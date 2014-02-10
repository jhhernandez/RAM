/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2014  Juan Hernández Hernández <janukato@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Program.h"

#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <boost/regex.hpp>
#include <string>

using namespace std;
using namespace boost;

Program::Program() {

}

Program::Program(const Program& other) {

}

Program::~Program() {

}

Program& Program::operator=(const Program& other) {

}

const vector<string> Program::tokenize(const string& str)  {
	vector<string> tokens;
	int32_t wspos;
	int32_t word_end;

	//cout << "Tokenizing " << str << endl;

	for (int32_t i = 0; i < str.size();) {
		wspos = str.find_first_not_of(" ", i);

		if (str[wspos] == ';') {
			// cout << "Token is a comment, pushing and breaking." << endl;
			// cout << str.substr(i, str.size() - i) << endl;
			tokens.push_back(str.substr(i, str.size() - i));
			break;
		}

		word_end = str.find_first_of(" ", wspos);
		// cout << "Token " << str.substr(wspos, word_end - wspos) << endl;
		tokens.push_back(str.substr(wspos, word_end - wspos));
		i = word_end;
	}

	return tokens;
}

int32_t Program::LLparser(const vector<vector<string> >& strings) {
	/* NTS TS Rule*/
	map<Symbol, map<Symbol, int32_t> > table;
	stack<Symbol> symStack;
	Symbol currSym;
	int32_t rule;
	vector<Symbol> la;

	// table setup
	// marker
	table[NTS_S][TS_MARKER] = 1;
	// comment
	table[NTS_S][TS_COMMENT] = 3;
	// inst
	// inst0
	table[NTS_S][TS_INST_0] = 2;
	table[NTS_INST][TS_INST_0] = 12;
	// inst1label
	table[NTS_S][TS_INST_1_LAB] = 2;
	table[NTS_INST][TS_INST_1_LAB] = 13;
	// inst1op
	table[NTS_S][TS_INST_1_OP] = 2;
	table[NTS_INST][TS_INST_1_OP] = 14;
	// operand
	// imm
	table[NTS_S][TS_OP_IMM]  = 2;
	table[NTS_INST][TS_OP_IMM] = 14;
	table[NTS_OPERAND][TS_OP_IMM] = 15;
	// direct
	table[NTS_S][TS_OP_DIRECT]  = 2;
	table[NTS_INST][TS_OP_DIRECT] = 14;
	table[NTS_OPERAND][TS_OP_DIRECT] = 16;
	// indirect
	table[NTS_S][TS_OP_INDIRECT]  = 2;
	table[NTS_INST][TS_OP_INDIRECT] = 14;
	table[NTS_OPERAND][TS_OP_INDIRECT] = 17;

	for (vector<vector<string> >::const_iterator i = strings.begin(); i != strings.end(); ++i) {
		// stack init
		while (!symStack.empty()) {
			symStack.pop();
		}
		symStack.push(NONE);
		symStack.push(NTS_S);
		int32_t j = 0;

		while (!symStack.empty()) {
			currSym = lexer((*i)[j]);
			cout << "Current symbol: " << symToString(currSym) << endl;
			cout << "Stack top: " << symToString(symStack.top()) << endl;

			if (currSym == symStack.top()) {
				cout << "Matched symbols: " << symToString(lexer((*i)[j])) << endl;
				++j;
				symStack.pop();
			} else {
				// lookahead para NTS == NTS_S
				/*
					1. NTS_S -> TS_MARKER
					2. NTS_S -> NTS_INST
					3. NTS_S -> TS_COMMENT
					4. NTS_S -> NTS_MARKER_INST
					5. NTS_S -> NTS_INST_COMMENT
					6. NTS_S -> NTS_MARKER_INST_COMMENT
				*/
				if (symStack.top() == NTS_S) {
					cout << "top == NTS_S" << endl;
					cout << "size = " << (*i).size() << endl;
					cin.get();

					if ((*i).size() > 1) {
						Symbol la1;

						if (currSym == TS_MARKER) {
							la1 = lexer((*i)[j + 1]);

							if (la1 == NTS_INST) {
								rule = 8;
							} else if (la1 == TS_COMMENT) {
								rule = 10;
							}
						}

						if (currSym == TS_INST_0) {
							la1 = lexer((*i)[j + 1]);

							if (la1 == TS_COMMENT) {
								rule = 9;
							}
						}

						if (currSym == TS_INST_1_LAB || currSym == TS_INST_1_OP) {
							la1 = lexer((*i)[j + 2]);

							if (la1 == TS_COMMENT) {
								rule = 9;
							}
						}

						if ((*i).size() > 2) {
							Symbol la2;

							if (la1 == TS_INST_0) {
								la2 = lexer((*i)[j + 2]);
							}

							if (currSym == TS_MARKER && la2 == TS_COMMENT) {
								if (la1 == TS_INST_0) {
									rule = 11;	
								}
							}

							if ((*i).size() > 3) {

							}
						}
					} else {
						rule = table[symStack.top()][currSym];
					}
				} else {
					rule = table[symStack.top()][currSym];
				}

				cout << "Rule " << rule << endl;

				switch (rule) {
				case 1:
					symStack.pop();
					symStack.push(TS_MARKER);
					break;

				case 2:
					symStack.pop();
					symStack.push(NTS_INST);
					break;

				case 3:
					symStack.pop();
					symStack.push(TS_COMMENT);
					break;

				case 4:
					symStack.pop();
					break;

				case 5:
					symStack.pop();
					break;

				case 6:
					symStack.pop();
					break;

				case 7:
					symStack.pop();
					break;

				case 8:
					symStack.pop();
					break;

				case 9:
					symStack.pop();
					symStack.push(TS_COMMENT);
					symStack.push(NTS_INST);
					break;

				case 10:
					symStack.pop();
					break;

				case 11:
					symStack.pop();
					break;

				case 12:
					symStack.pop();
					symStack.push(TS_INST_0);
					break;

				case 13:
					symStack.pop();
					symStack.push(TS_LABEL);
					symStack.push(TS_INST_1_LAB);
					break;

				case 14:
					symStack.pop();
					symStack.push(NTS_OPERAND);
					symStack.push(TS_INST_1_OP);
					break;

				case 15:
					symStack.pop();
					symStack.push(TS_OP_IMM);
					break;

				case 16:
					symStack.pop();
					symStack.push(TS_OP_DIRECT);
					break;

				case 17:
					symStack.pop();
					symStack.push(TS_OP_INDIRECT);
					break;

				default:
					cout << "default" << endl;
					return 0;
					break;
				}
			}
		}

		cin.get();
	}

	cout << "Done parsing" << endl;
	return 0;
}

Program::Symbol Program::lexer(const string& str) {
	regex label("\\s*[_a-z][a-z]*\\s*");
	regex marker("\\s*[_a-z][a-z]*:?\\s*");
	regex instruction("\\s*(?:READ|WRITE|LOAD|STORE|ADD|SUB|DIV|MULT|HALT|JUMP|JGTZ|JZERO)\\s*");
	regex inst0("\\s*HALT\\s*");
	regex inst1label("\\s*JUMP|JGTZ|JZERO\\s*");
	regex comment("\\s*;.*$");
	regex operand("\\s*[=*]?\\d+\\s*");
	regex opimm("\\s*=\\d+\\s*");
	regex opind("\\s*\\*\\d+\\s*");

	if (regex_match(str, marker)) {
		if (regex_match(str, label)) {
			return TS_LABEL;
		}

		return TS_MARKER;
	} else if (regex_match(str, instruction)) {
		if (regex_match(str, inst0)) {
			return TS_INST_0;
		} else if (regex_match(str, inst1label)) {
			return TS_INST_1_LAB;
		}

		return TS_INST_1_OP;
	} else if (regex_match(str, comment)) {
		return TS_COMMENT;
	} else if (regex_match(str, operand)) {
		if (regex_match(str, opimm)) {
			return TS_OP_IMM;
		} else if (regex_match(str, opind)) {
			return TS_OP_INDIRECT;
		}

		return TS_OP_DIRECT;
	} else {
		return NONE;
	}
}

int32_t Program::readFile(const char* file) {
	ifstream ifs(file);
	string line;
	vector<vector<string> > program;
	vector<string> vecline;

	if (!ifs.is_open() || ifs.bad()) {
		return -1;
	}

	while (!ifs.eof()) {
		getline(ifs, line);

		if (!line.empty()) {
			program.push_back(tokenize(line));
		}
	}
	
// 	for (vector<vector<string> >::const_iterator i = program.begin(); i != program.end(); ++i) {
// 		for (vector<string>::const_iterator j = (*i).begin(); j != (*i).end(); ++j) {
// 			cout << " Token: " << (*j);
// 		}
// 		cout << endl;
// 	}
// 	
// 	cin.get();
	LLparser(program);

	return 0;
}

const string Program::symToString(Symbol sym) {
	string str;

	switch (sym) {
	case NONE:
		str = "NONE";
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

