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

#include <sstream>

using namespace std;

Program::Program(const char* cstr) {
	Parser p;

	if (p.readFile(cstr) == 0) {
		m_program = p.program();
		m_labels = p.labels();
		
		m_assembledProgram.resize(m_program.size());

		assemble();
	}
}

Program::~Program() {

}

void Program::assemble() {
	uint32_t line = 0;
	OPCode tmpOP;
	int32_t tmpValue;
	
	for (auto it : m_program) {
		tmpValue = 0;

		for (auto itt : it) {
			switch (itt.second) {
			case TS_INST_0:
				tmpOP = HALT;
				break;

			case TS_INST_1_OP:
				if (itt.first == "ADD") {
					tmpOP = ADD;
				} else if (itt.first == "SUB") {
					tmpOP = SUB;
				} else if (itt.first == "MULT") {
					tmpOP = MULT;
				} else if(itt.first == "DIV") {
					tmpOP = DIV;
				} else if (itt.first == "LOAD") {
					tmpOP = LOAD;
				} else if (itt.first == "STORE") {
					tmpOP = STORE;
				} else if (itt.first == "READ") {
					tmpOP = READ;
				} else {
					tmpOP = WRITE;
				}

				break;

			case TS_INST_1_LAB:
				if (itt.first == "JUMP") {
					tmpOP = JUMP;
				} else if (itt.first == "JGTZ") {
					tmpOP = JGTZ;
				} else {
					tmpOP = JZERO;
				}

				break;

			case TS_OP_IMM:
				tmpOP = static_cast<OPCode>(tmpOP | IMM);
				stringstream(itt.first.substr(1, itt.first.size() - 1)) >> tmpValue;
				break;

			case TS_OP_DIRECT:
				tmpOP = static_cast<OPCode>(tmpOP | DIRECT);
				stringstream(itt.first) >> tmpValue;
				break;

			case TS_OP_INDIRECT:
				tmpOP = static_cast<OPCode>(tmpOP | INDIRECT);
				stringstream(itt.first.substr(1, itt.first.size() - 1)) >> tmpValue;
				break;

			case TS_LABEL:
				tmpValue = m_labels[itt.first];
				break;
			}
		}

		m_assembledProgram[line++] = pair<OPCode, int32_t>(tmpOP, tmpValue);
	}
}
