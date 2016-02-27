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

using std::string;
using std::stringstream;
using std::pair;

Program::Program(const string& _file)
{
	Parser p{_file};

	m_program = p.program();
	m_labels = p.labels();

	m_assembledProgram.resize(m_program.size());

	assemble();
}

void Program::assemble()
{
	uint32_t line = 0;
	OPCode tmpOP;
	int32_t tmpValue;

	for (const auto& it : m_program) {
		tmpValue = 0;

		for (const auto& jt : it) {
			switch (jt.second) {
			case Symbol::TS_INST_0:
				tmpOP = OPCode::HALT;
				break;

			case Symbol::TS_INST_1_OP:
				if (jt.first == "ADD") {
					tmpOP = OPCode::ADD;
				} else if (jt.first == "SUB") {
					tmpOP = OPCode::SUB;
				} else if (jt.first == "MULT") {
					tmpOP = OPCode::MULT;
				} else if (jt.first == "DIV") {
					tmpOP = OPCode::DIV;
				} else if (jt.first == "LOAD") {
					tmpOP = OPCode::LOAD;
				} else if (jt.first == "STORE") {
					tmpOP = OPCode::STORE;
				} else if (jt.first == "READ") {
					tmpOP = OPCode::READ;
				} else {
					tmpOP = OPCode::WRITE;
				}

				break;

			case Symbol::TS_INST_1_LAB:
				if (jt.first == "JUMP") {
					tmpOP = OPCode::JUMP;
				} else if (jt.first == "JGTZ") {
					tmpOP = OPCode::JGTZ;
				} else {
					tmpOP = OPCode::JZERO;
				}

				break;

			case Symbol::TS_OP_IMM:
				tmpOP = static_cast<OPCode>(tmpOP | OPCode::IMM);
				stringstream(jt.first.substr(1, jt.first.size() - 1)) >> tmpValue;
				break;

			case Symbol::TS_OP_DIRECT:
				tmpOP = static_cast<OPCode>(tmpOP | OPCode::DIRECT);
				stringstream(jt.first) >> tmpValue;
				break;

			case Symbol::TS_OP_INDIRECT:
				tmpOP = static_cast<OPCode>(tmpOP | OPCode::INDIRECT);
				stringstream(jt.first.substr(1, jt.first.size() - 1)) >> tmpValue;
				break;

			case Symbol::TS_LABEL:
				tmpValue = m_labels[jt.first];
				break;
			default:
				break;
			}
		}

		m_assembledProgram[line++] = pair<OPCode, int32_t>(tmpOP, tmpValue);
	}
}
