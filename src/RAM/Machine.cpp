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
#include "Tape.h"
#include "ITape.h"
#include "OTape.h"
#include <iostream>
#include <curses.h>

using namespace std;

Machine::Machine() :
	m_program(NULL), m_inputTape(NULL), m_outputTape(NULL), m_instPointer(0) {
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

uint32_t Machine::run() {
	m_instPointer = 0;

	if (m_program != NULL && m_inputTape != NULL && m_outputTape != NULL) {
		while (m_currentOP != HALT) {
			m_currentOP = m_program->program()[m_instPointer].first;
			cout << m_currentOP << endl;

			switch (m_currentOP & 0xE0) {
			case 0x20: // ARITMÉTICAS
				arithmeticOps(m_program->program()[m_instPointer]);
				break;

			case 0x40: // REGISTROS
				registerOps(m_program->program()[m_instPointer]);
				break;

			case  0x80: // SALTOS
				jumpOps(m_program->program()[m_instPointer]);
				break;

			default:
				break;
			}
		}

		m_outputTape->save();
		return 0;
	}

	return -1;
}

void Machine::arithmeticOps(std::pair<OPCode, int32_t> oper) {
	int32_t tempOperand;

	switch (oper.first & 0x1C) {
	case IMM:
		tempOperand = oper.second;
		break;

	case DIRECT:
		tempOperand = (*m_registers)[oper.second];
		break;

	case INDIRECT:
		tempOperand = (*m_registers)[(*m_registers)[oper.second]];
		break;
	}

	switch (oper.first & 0x3) { // FIXME: No se comprueban desbordamientos
	case ADD:
		m_registers->setACC(m_registers->getACC() + tempOperand);
		break;

	case SUB:
		m_registers->setACC(m_registers->getACC() - tempOperand);
		break;

	case MULT:
		m_registers->setACC(m_registers->getACC() * tempOperand);
		break;

	case DIV:
		if (tempOperand == 0) {
			m_currentOP = HALT;
		} else {
			m_registers->setACC(m_registers->getACC() / tempOperand);
		}

		break;
	}

	++m_instPointer;
}

void Machine::registerOps(std::pair<OPCode, int32_t> oper) {
	int32_t tempOperand;

	switch (oper.first & 0x1C) {
	case IMM:
		tempOperand = oper.second;
		break;

	case DIRECT:
		tempOperand = (*m_registers)[oper.second];
		break;

	case INDIRECT:
		tempOperand = (*m_registers)[(*m_registers)[oper.second]];
		break;
	}

	switch (oper.first & 0x3) {
	case LOAD:
		m_registers->setACC(tempOperand);
		break;

	case STORE:
		(*m_registers)[tempOperand] = m_registers->getACC();
		break;

	case READ:
		(*m_registers)[tempOperand] = m_inputTape->read();
		break;

	case WRITE:
		break;
	}

	++m_instPointer;
}

void Machine::jumpOps(std::pair<OPCode, int32_t> oper) {
	switch (oper.first) {
	case JUMP:
		m_instPointer = oper.second;
		break;

	case JGTZ:
		if (m_registers->getACC() > 0) {
			m_instPointer = oper.second;
		} else {
			++m_instPointer;
		}

		break;

	case JZERO:
		if (m_registers->getACC() == 0) {
			m_instPointer = oper.second;
		} else {
			++m_instPointer;
		}

		break;
	}
}

void Machine::debug() {
	m_instPointer = 0;
	m_currentOP = m_program->program()[m_instPointer].first;
}

void Machine::step() {
	printw("%d %d\n", m_currentOP, m_program->program()[m_instPointer].second);

	switch (m_currentOP & 0xE0) {
	case 0x20: // ARITMÉTICAS
		arithmeticOps(m_program->program()[m_instPointer]);
		break;

	case 0x40: // REGISTROS
		registerOps(m_program->program()[m_instPointer]);
		break;

	case  0x80: // SALTOS
		jumpOps(m_program->program()[m_instPointer]);
		break;

	default:
		break;
	}
	
	m_currentOP = m_program->program()[m_instPointer].first;
}
