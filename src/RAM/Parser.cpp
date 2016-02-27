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
#include <stack>
#include <regex>
#include <boost/algorithm/string.hpp>

using std::string;
using std::ifstream;
using std::vector;
using std::regex;
using std::regex_match;
using std::cout;
using std::cin;
using std::endl;
using std::map;
using std::stack;

using boost::trim_left;
using boost::trim_right;

Parser::Parser(const std::string& _file)
{
	m_program.resize(0);

	readFile(_file);
}

const vector<strSymPair> Parser::tokenize(const string& _str)
{
	vector<strSymPair> tokens;
	string substr;
	int32_t whitespace_position;
	int32_t word_end;
	Symbol symbol;

	for (uint32_t i = 0; i < _str.size();) {
		whitespace_position = _str.find_first_not_of(" ", i);

		if (_str[whitespace_position] == ';') {
			substr = _str.substr(i, _str.size() - i);
			tokens.push_back(strSymPair(substr, Symbol::TS_COMMENT));
			break;
		}

		word_end = _str.find_first_of(" ", whitespace_position);
		symbol = lexer(_str.substr(whitespace_position, word_end - whitespace_position));

		if (symbol == Symbol::TS_LABEL) {  // Hack para Symbol::TS_MARKER con : separados
			int32_t tp_start;
			int32_t tp_end;
			string label;

			label = _str.substr(whitespace_position, word_end - whitespace_position);
			trim_left(label);
			trim_right(label);

			tp_start = _str.find_first_not_of(" ", word_end);
			tp_end = _str.find_first_of(" ", tp_start);

			if (tp_start >= 0 && tp_start < _str.size() && tp_end >= 0 && tp_end < _str.size()) {
				substr = _str.substr(tp_start, tp_end - tp_start);

				if (lexer(substr) == Symbol::TS_TP) {
					tokens.push_back(strSymPair(label + ":", Symbol::TS_MARKER));
					i = tp_end;
					continue;
				}
			}
		}

		if (symbol == Symbol::NONE) {
			cout << "ERROR: " << _str.substr(whitespace_position, word_end - whitespace_position) <<
			     " no corresponde a ningún símbolo válido" << endl;
		}

		substr = _str.substr(whitespace_position, word_end - whitespace_position);
		trim_right(substr);
		trim_left(substr);
		tokens.push_back(strSymPair(substr, symbol));
		i = word_end;
	}

	tokens.push_back(strSymPair("", Symbol::TS_EOL));

	return tokens;
}

// FIXME: use exceptions instead of return values
int32_t Parser::parse(std::vector<std::vector<strSymPair>> program)
{
	/* LH RH Rule*/
	map<Symbol, map<Symbol, uint32_t>> table;
	stack<Symbol> symbol_stack;
	Symbol current_symbol;
	int32_t rule;
	uint32_t line = 0;

	// table setup
	// Symbol::NTS_S
	table[Symbol::NTS_S][Symbol::TS_MARKER] = 1;
	table[Symbol::NTS_S][Symbol::TS_INST_0] = 2;
	table[Symbol::NTS_S][Symbol::TS_INST_1_LAB] = 2;
	table[Symbol::NTS_S][Symbol::TS_INST_1_OP] = 2;
	table[Symbol::NTS_S][Symbol::TS_COMMENT] = 3;
	// Symbol::NTS_A
	table[Symbol::NTS_A][Symbol::TS_COMMENT] = 5;
	table[Symbol::NTS_A][Symbol::TS_INST_0] = 4;
	table[Symbol::NTS_A][Symbol::TS_INST_1_LAB] = 4;
	table[Symbol::NTS_A][Symbol::TS_INST_1_OP] = 4;
	table[Symbol::NTS_A][Symbol::TS_EOL] = 6;
	// Symbol::NTS_B
	table[Symbol::NTS_B][Symbol::TS_COMMENT] = 7;
	table[Symbol::NTS_B][Symbol::TS_EOL] = 8;
	// Symbol::NTS_INST
	table[Symbol::NTS_INST][Symbol::TS_INST_0] = 9;
	table[Symbol::NTS_INST][Symbol::TS_INST_1_LAB] = 10;
	table[Symbol::NTS_INST][Symbol::TS_INST_1_OP] = 11;
	// Symbol::NTS_OPERAND
	table[Symbol::NTS_OPERAND][Symbol::TS_OP_IMM] = 12;
	table[Symbol::NTS_OPERAND][Symbol::TS_OP_DIRECT] = 13;
	table[Symbol::NTS_OPERAND][Symbol::TS_OP_INDIRECT] = 14;

	for (auto it : program) {
		vector<strSymPair>::const_iterator j;

		// stack init
		while (!symbol_stack.empty()) {
			symbol_stack.pop();
		}

		symbol_stack.push(Symbol::TS_EOL);
		symbol_stack.push(Symbol::NTS_S);

		j = it.begin();
// 		line = i - program.begin();

		while (!symbol_stack.empty()) {
			current_symbol = (*j).second;

			if (current_symbol == symbol_stack.top()) {

				++j;
				symbol_stack.pop();
			} else {
				rule = table[symbol_stack.top()][current_symbol];

				switch (rule) {
				case 1:
					symbol_stack.pop();
					symbol_stack.push(Symbol::NTS_A);
					symbol_stack.push(Symbol::TS_MARKER);
					break;

				case 2:
					symbol_stack.pop();
					symbol_stack.push(Symbol::NTS_B);
					symbol_stack.push(Symbol::NTS_INST);
					break;

				case 3:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_COMMENT);
					break;

				case 4:
					symbol_stack.pop();
					symbol_stack.push(Symbol::NTS_B);
					symbol_stack.push(Symbol::NTS_INST);
					break;

				case 5:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_COMMENT);
					break;

				case 6:
					symbol_stack.pop();
					break;

				case 7:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_COMMENT);
					break;

				case 8:
					symbol_stack.pop();
					break;

				case 9:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_INST_0);
					break;

				case 10:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_LABEL);
					symbol_stack.push(Symbol::TS_INST_1_LAB);
					break;

				case 11:
					symbol_stack.pop();
					symbol_stack.push(Symbol::NTS_OPERAND);
					symbol_stack.push(Symbol::TS_INST_1_OP);
					break;

				case 12:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_OP_IMM);
					break;

				case 13:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_OP_DIRECT);
					break;

				case 14:
					symbol_stack.pop();
					symbol_stack.push(Symbol::TS_OP_INDIRECT);
					break;

				default:
					/*
					 * FIXME: should not print any output but
					 * throw with some meaningful message
					 */
					
					cout << "Parsing failed at line " << line << ": ";

					for (vector<strSymPair>::const_iterator k = it.begin(); k != it.end(); ++k) {
						cout << (*k).first << " ";
					}

					cout << endl;
					cout << "\t\t\t\t"; // FIXME: Deja >= 25 espacios

					for (vector<strSymPair>::const_iterator k = it.begin(); k != it.end(); ++k) {
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
	}

	return 0;
}

Symbol Parser::lexer(const string& str)
{
	regex label("\\s*[_a-z][a-z]*\\s*");
	regex marker("^\\s*[_a-z][a-z]*\\s*:\\s*");
	regex instruction("\\s*(?:READ|WRITE|LOAD|STORE|ADD|SUB|DIV|MULT|HALT|JUMP|JGTZ|JZERO)\\s*");
	regex inst0("\\s*HALT\\s*");
	regex inst1label("\\s*JUMP|JGTZ|JZERO\\s*");
	regex comment("\\s*;.*$");
	regex operand("\\s*[=*]?\\d+\\s*");
	regex opimm("\\s*=\\d+\\s*");
	regex opind("\\s*\\*\\d+\\s*");
	regex tp("\\s*:\\s*");

	if (regex_match(str, marker)) {
		return Symbol::TS_MARKER;
	} else if (regex_match(str, label)) {
		return Symbol::TS_LABEL;
	} else if (regex_match(str, instruction)) {
		if (regex_match(str, inst0)) {
			return Symbol::TS_INST_0;
		} else if (regex_match(str, inst1label)) {
			return Symbol::TS_INST_1_LAB;
		}

		return Symbol::TS_INST_1_OP;
	} else if (regex_match(str, comment)) {
		return Symbol::TS_COMMENT;
	} else if (regex_match(str, operand)) {
		if (regex_match(str, opimm)) {
			return Symbol::TS_OP_IMM;
		} else if (regex_match(str, opind)) {
			return Symbol::TS_OP_INDIRECT;
		}

		return Symbol::TS_OP_DIRECT;
	} else if (regex_match(str, tp)) {
		return Symbol::TS_TP;
	} else {
		return Symbol::NONE;
	}
}

int32_t Parser::readFile(const string& _file)
{
	std::vector<std::vector<strSymPair> > program;
	ifstream ifs(_file);
	string line;
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

	parse(program);

	/*
	 * strips comments and replaces labels with instruction line for branching
	 * to build the m_program object
	 */
	for (const auto & it : program) {
		if (it[0].second != Symbol::TS_COMMENT) {
			m_program.push_back(it);

			if (it[0].second == Symbol::TS_MARKER) {
				if (m_labels.count(it[0].first.substr(0, it[0].first.size() - 1)) == 0) {
					m_labels[it[0].first.substr(0, it[0].first.size() - 1)] = m_program.size() - 1;
				} else {
					return -1;
				}
			}
		}
	}

	return 0;
}
