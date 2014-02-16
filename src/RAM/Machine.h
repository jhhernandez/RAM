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

#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <stdint.h>
#include "Registers.h"
#include "Program.h"

class Program;
class Registers;
class ITape;
class OTape;

class Machine {
public:
	Machine();
	~Machine();
	uint32_t programFile(const char*);
	uint32_t inputFile(const char*);
	uint32_t outputFile(const char*);
	uint32_t execute();

	const std::vector<int32_t>& showRegisters() {
		return m_registers->show();
	}

	const std::vector<std::vector<strSymPair> >& showProgram() {
		return m_program->program();
	}
private:
	Program* m_program;
	Registers* m_registers;
	ITape* m_inputTape;
	OTape* m_outputTape;
	std::string m_trace;
};

#endif // MACHINE_H
