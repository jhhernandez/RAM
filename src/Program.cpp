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
#include "Parser.h"

#include <iostream>

using namespace std;

Program::Program(const char* cstr) {
	Parser p;
	p.readFile(cstr);
    //p.parse();
	
	m_program = p.program();
}

Program::~Program() {

}


void Program::showProgram() {
	for (vector<vector<pair<string, Symbol> > >::iterator i = m_program.begin(); i != m_program.end(); ++i) {
		cout << "I[" << i - m_program.begin() << "]";

		for (vector<pair<string, Symbol> >::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			cout << " " << (*j).first;
		}

		cout << endl;
	}
}

void Program::showTokenizedProgram() {
	for (vector<vector<pair<string, Symbol> > >::iterator i = m_program.begin(); i != m_program.end(); ++i) {
		cout << "I[" << i - m_program.begin() << "]";

		for (vector<pair<string, Symbol> >::iterator j = (*i).begin(); j != (*i).end(); ++j) {
			cout << " " << symToString((*j).second);
		}

		cout << endl;
	}
}
