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

#include "Machine.h"

#include <stddef.h>

#include "Program.h"
#include "Registers.h"
#include "ITape.h"
#include "OTape.h"

Machine::Machine() : m_program(NULL), m_inputTape(NULL), m_outputTape(NULL) {
	m_registers = new Registers;
}

Machine::~Machine() {
	if (m_program != NULL) {
		delete m_program;
		m_program = NULL;
	}

	if (m_inputTape != NULL) {
		delete m_inputTape;
		m_inputTape = NULL;
	}

	if (m_outputTape != NULL) {
		delete m_outputTape;
		m_outputTape = NULL;
	}

	if (m_registers != NULL) {
		delete m_registers;
		m_registers = NULL;
	}
}

uint32_t Machine::programFile(const char* file) {
	m_program = new Program(file);
}

uint32_t Machine::inputFile(const char* file) {
	m_inputTape = new ITape(file);
}

uint32_t Machine::outputFile(const char* file) {
	m_outputTape = new OTape(file);
}

uint32_t Machine::execute() {
	if (m_program != NULL && m_inputTape != NULL && m_outputTape != NULL) {
		return 0;
	}

	return -1;
}

