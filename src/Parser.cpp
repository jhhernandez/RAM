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

	for (uint32_t i = 0; i < str.size();) {
		wspos = str.find_first_not_of(" ", i);

		if (str[wspos] == ';') {
			tokens.push_back(strSymPair(str.substr(i, str.size() - i), TS_COMMENT));
			break;
		}

		word_end = str.find_first_of(" ", wspos);
		tokens.push_back(strSymPair(str.substr(wspos, word_end - wspos),
		                            lexer(str.substr(wspos, word_end - wspos))));
		i = word_end;
	}

    tokens.push_back(strSymPair("", NONE));

	return tokens;
}

int32_t Parser::parse() {
	/* LH RH Rule*/
	map<Symbol, vector<symRulePair> > vtable;
	stack<Symbol> symStack;
	Symbol currSym;
	int32_t rule;

	// table setup
    // marker
    // comment
    // inst
    // inst0
    // inst1label
    // inst1op
	// operand
    // imm
    // direct
    // indirect

	for (vector<vector<strSymPair> >::const_iterator i = m_program.begin(); i != m_program.end(); ++i) {
		vector<strSymPair>::const_iterator j;

		// stack init
		while (!symStack.empty()) {
			symStack.pop();
		}

		symStack.push(NONE);
		symStack.push(NTS_S);

		j = (*i).begin();
		cout << "Parsing line " << i - m_program.begin() << ", size= " << (*i).size() << endl;


		while (!symStack.empty()) {
			currSym = (*j).second;
			cout << "Current symbol: " << symToString(currSym) << endl;
			cout << "Stack top: " << symToString(symStack.top()) << endl;

			if (currSym == symStack.top()) {
				cout << "Matched symbols: " << symToString((*j).second) << endl;
				++j;
				symStack.pop();
			} else {
				cout << "Comprobando reglas del vector " << symToString(symStack.top()) << endl;
				cin.get();

				for (vector<symRulePair>::iterator k = vtable[symStack.top()].begin();
				                k != vtable[symStack.top()].end(); ++k) {
					cout << symToString((*k).first) << endl;
					if ((*k).first == currSym) {
						rule = (*k).second;
						cout << "Rule found for symbol " << symToString(currSym) << ", using rule " << rule << endl;
						break;
					}
				}

				switch (rule) {
				case 1:
					symStack.pop();
					for (vector<strSymPair>::const_iterator m = (*i).end(); m != j; --m) {
						symStack.push((*m).second);
					}
					break;

				case 2:
					symStack.pop();
					break;

				case 3:
					symStack.pop();
					symStack.push(TS_LABEL);
					break;

				case 4:
					symStack.pop();
					symStack.push(NTS_OPERAND);
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

				default:
					cout << "Parsing failed" << endl;
					return -1;
					break;
				}
			}
		}

		cout << "line parsed" << endl;
		cin.get();
	}

	cout << "Done parsing" << endl;
	return 0;
}

Symbol Parser::lexer(const string& str) {
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
