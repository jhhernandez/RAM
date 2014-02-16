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
	if (p.readFile(cstr) == 0) {
		m_program = p.program();
		m_labels = p.labels();
		
		assemble();
	}
}

Program::~Program() {

}

void Program::assemble() {
	for (vector<vector<strSymPair> >::iterator i = m_program.begin();
	     i != m_program.end(); ++i) {
		for (vector<strSymPair>::iterator j = (*i).begin();
		     j != (*i).end(); ++j) {
			
		}
	}
}