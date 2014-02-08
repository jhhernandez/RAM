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
#include "ParserException.h"

#include <iostream>
#include <fstream>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <regex>

using namespace std;

Program::Program() {

}

Program::Program(const Program& other) {

}

Program::~Program() {

}

Program& Program::operator=(const Program& other) {

}

int readFile(const char* file) {
	vector<string> program;
	ifstream ifs(file);

	if (!ifs.is_open() || ifs.bad()) {
		return -1;
	}
	
	if (ifs.is_open()) {
		ifs.close();
	}
	return 0;
}

int Program::parser() {
	map<Symbol, map<Symbol, int> > table;
}

Program::Symbol Program::lexer(const char* cstr) {
	regex label("^\\s*[_a-zA-Z]\\w*\\s*:");
	regex instruction("READ|WRITE|LOAD|STORE|ADD|SUB|DIV|MULT|HALT|JUMP|JGTZ|JZERO");
	regex comment("\\s*:\\w*\\s*$");
	regex operand("");
}
