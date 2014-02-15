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

#include "Parser.h"

#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <boost/regex.hpp>

using namespace std;
using namespace boost;

Parser::Parser() {

}

Parser::~Parser() {

}

const vector<strSymPair> Parser::tokenize(const string& str)  {
	vector<strSymPair> tokens;
	int32_t wspos;
	int32_t word_end;
	Symbol symbol;

	for (uint32_t i = 0; i < str.size();) {
		wspos = str.find_first_not_of(" ", i);

		if (str[wspos] == ';') {
			tokens.push_back(strSymPair(str.substr(i, str.size() - i), TS_COMMENT));
			break;
		}

		word_end = str.find_first_of(" ", wspos);
		symbol = lexer(str.substr(wspos, word_end - wspos));
		if (symbol == NONE) {
			cout << "ERROR: " << str.substr(wspos, word_end - wspos) <<
					" no corresponde a ningún símbolo válido" << endl;
		}
		tokens.push_back(strSymPair(str.substr(wspos, word_end - wspos), symbol));
		i = word_end;
	}

	tokens.push_back(strSymPair("", TS_EOL));

	return tokens;
}

int32_t Parser::parse() {
	/* LH RH Rule*/
	map<Symbol, map<Symbol, uint32_t> > table;
	stack<Symbol> symStack;
	Symbol currSym;
	int32_t rule;
	uint32_t line;

	// table setup
	// NTS_S
	table[NTS_S][TS_MARKER] = 1;
	table[NTS_S][TS_INST_0] = 2;
	table[NTS_S][TS_INST_1_LAB] = 2;
	table[NTS_S][TS_INST_1_OP] = 2;
	table[NTS_S][TS_COMMENT] = 3;
	// NTS_A
	table[NTS_A][TS_COMMENT] = 5;
	table[NTS_A][TS_INST_0] = 4;
	table[NTS_A][TS_INST_1_LAB] = 4;
	table[NTS_A][TS_INST_1_OP] = 4;
	table[NTS_A][TS_EOL] = 6;
	// NTS_B
	table[NTS_B][TS_COMMENT] = 7;
	table[NTS_B][TS_EOL] = 8;
	// NTS_INST
	table[NTS_INST][TS_INST_0] = 9;
	table[NTS_INST][TS_INST_1_LAB] = 10;
	table[NTS_INST][TS_INST_1_OP] = 11;
	// NTS_OPERAND
	table[NTS_OPERAND][TS_OP_IMM] = 12;
	table[NTS_OPERAND][TS_OP_DIRECT] = 13;
	table[NTS_OPERAND][TS_OP_INDIRECT] = 14;

	for (vector<vector<strSymPair> >::const_iterator i = m_program.begin(); i != m_program.end(); ++i) {
		vector<strSymPair>::const_iterator j;

		// stack init
		while (!symStack.empty()) {
			symStack.pop();
		}

		symStack.push(TS_EOL);
		symStack.push(NTS_S);

		j = (*i).begin();
		line = i - m_program.begin();
		cout << "Parsing line " << line << endl;


		while (!symStack.empty()) {
			currSym = (*j).second;
			cout << "Current symbol: " << symToString(currSym) << endl;
			cout << "Stack top: " << symToString(symStack.top()) << endl;

			if (currSym == symStack.top()) {
				cout << "Matched symbols: " << symToString((*j).second) << endl;
				++j;
				symStack.pop();
			} else {
				rule = table[symStack.top()][currSym];
				cout << "Regla " << rule << endl;

				switch (rule) {
				case 1:
					symStack.pop();
					symStack.push(NTS_A);
					symStack.push(TS_MARKER);
					break;

				case 2:
					symStack.pop();
					symStack.push(NTS_B);
					symStack.push(NTS_INST);
					break;

				case 3:
					symStack.pop();
					symStack.push(TS_COMMENT);
					break;

				case 4:
					symStack.pop();
					symStack.push(NTS_B);
					symStack.push(NTS_INST);
					break;

				case 5:
					symStack.pop();
					symStack.push(TS_COMMENT);
					break;

				case 6:
					symStack.pop();
					break;

				case 7:
					symStack.pop();
					symStack.push(TS_COMMENT);
					break;

				case 8:
					symStack.pop();
					break;

				case 9:
					symStack.pop();
					symStack.push(TS_INST_0);
					break;

				case 10:
					symStack.pop();
					symStack.push(TS_LABEL);
					symStack.push(TS_INST_1_LAB);
					break;

				case 11:
					symStack.pop();
					symStack.push(NTS_OPERAND);
					symStack.push(TS_INST_1_OP);
					break;

				case 12:
					symStack.pop();
					symStack.push(TS_OP_IMM);
					break;

				case 13:
					symStack.pop();
					symStack.push(TS_OP_DIRECT);
					break;

				case 14:
					symStack.pop();
					symStack.push(TS_OP_INDIRECT);
					break;

				default:
					cout << "Parsing failed at line " << line << ": ";
					for (vector<strSymPair>::const_iterator k = (*i).begin(); k != (*i).end(); ++k) {
						cout << (*k).first << " ";
					}
					cout << endl;
					cout << "\t\t\t\t"; // FIXME: Deja >= 25 espacios
					for (vector<strSymPair>::const_iterator k = (*i).begin(); k != (*i).end(); ++k) {
						if ((*k) == (*j)) {
							cout << "^" << endl;
						} else {
							// FIXME: Introducir espacios aqui dependiendo de tal y cual
						}
					}
					cout << endl;
					cin.get();

					return -1;
					break;
				}
			}
		}

		cout << "line parsed" << endl << endl;
	}

	cout << "Done parsing" << endl;
	return 0;
}

Symbol Parser::lexer(const string& str) {
	regex label("\\s*[_a-z][a-z]*\\s*");
	regex marker("^\\s*[_a-z][a-z]*\\s*:\\s*"); // FIXME: No funciona cuando los dos puntos no estan pegados a la etiqueta
	regex instruction("\\s*(?:READ|WRITE|LOAD|STORE|ADD|SUB|DIV|MULT|HALT|JUMP|JGTZ|JZERO)\\s*");
	regex inst0("\\s*HALT\\s*");
	regex inst1label("\\s*JUMP|JGTZ|JZERO\\s*");
	regex comment("\\s*;.*$");
	regex operand("\\s*[=*]?\\d+\\s*");
	regex opimm("\\s*=\\d+\\s*");
	regex opind("\\s*\\*\\d+\\s*");

	if (regex_match(str, marker)) {
		return TS_MARKER;
	} else if (regex_match(str, label)) {
		return TS_LABEL;
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

int32_t Parser::readFile(const char* file) {
	ifstream ifs(file);
	string line;
	vector<string> vecline;

	if (!ifs.is_open() || ifs.bad()) {
		return -1;
	}

	while (!ifs.eof()) {
		getline(ifs, line);

		if (!line.empty()) {
			m_program.push_back(tokenize(line));
		}
	}

	return 0;
}
