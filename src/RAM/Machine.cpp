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

#include "Program.h"
#include "Registers.h"
#include "Tape.h"
#include "ITape.h"
#include "OTape.h"
#include <iostream>
#include <curses.h>

using namespace std;

Machine::Machine() :
	m_program(NULL), m_inputTape(NULL), m_outputTape(NULL), m_instructionPointer(0)
{
	m_registers = new Registers;
}

Machine::~Machine()
{
	delete m_program;
	delete m_inputTape;
	delete m_outputTape;
	delete m_registers;
}

uint32_t Machine::programFile(const char* file)
{
	m_program = new Program(file);
}

uint32_t Machine::inputFile(const char* file)
{
	m_inputTape = new ITape(file);
}

uint32_t Machine::outputFile(const char* file)
{
	m_outputTape = new OTape(file);
}

uint32_t Machine::run()
{
	m_instructionPointer = 0;

	m_currentOP = m_program->program()[m_instructionPointer].first;

	if (m_program != NULL && m_inputTape != NULL && m_outputTape != NULL) {
		while (m_currentOP != HALT) {
			m_currentOP = m_program->program()[m_instructionPointer].first;
			switch (m_currentOP & 0xE0) {
			case 0x20: // ARITMÉTICAS
				arithmeticOps(m_program->program()[m_instructionPointer]);
				break;

			case 0x40: // REGISTROS
				registerOps(m_program->program()[m_instructionPointer]);
				break;

			case  0x80: // SALTOS
				jumpOps(m_program->program()[m_instructionPointer]);
				break;

			default:
				m_currentOP = HALT;
				break;
			}
		}

		m_outputTape->save();
		return 0;
	}

	return -1;
}

void Machine::arithmeticOps(std::pair<OPCode, int32_t> oper)
{
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

	switch (oper.first & 0x23) { // FIXME: No se comprueban desbordamientos
	case ADD:
		if (m_registers->getACC() + tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers->getACC() + tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = HALT;
			return;
		}
		m_registers->setACC(m_registers->getACC() + tempOperand);
		break;

	case SUB:
		if (m_registers->getACC() - tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers->getACC() - tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = HALT;
			return;
		}
		m_registers->setACC(m_registers->getACC() - tempOperand);
		break;

	case MULT:
		if (m_registers->getACC() * tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers->getACC() * tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = HALT;
			return;
		}
		m_registers->setACC(m_registers->getACC() * tempOperand);
		break;

	case DIV:
		if (tempOperand == 0) {
			m_machineState = ZERO_DIV;
			m_currentOP = HALT;
			return;
		} else {
			m_registers->setACC(m_registers->getACC() / tempOperand);
		}

		break;
	}

	++m_instructionPointer;
}

void Machine::registerOps(std::pair<OPCode, int32_t> oper)
{
	int32_t tempOperand;
	//printw("%d\n", oper.first);

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

	switch (oper.first & 0x43) {
	case LOAD: // Allows IMM, DIRECT and INDIRECT
		m_registers->setACC(tempOperand);
		break;

	case WRITE: // Allows IMM, DIRECT and INDIRECT
		m_outputTape->write(tempOperand);
		break;

	case STORE: // Doesn't allow IMM since the argument is necessarily a register
		switch (oper.first & 0x1C) {
		case DIRECT:
			tempOperand = oper.second;
			break;
		case INDIRECT:
			tempOperand = (*m_registers)[oper.second];
			break;
		}
		(*m_registers)[tempOperand] = m_registers->getACC();
		break;

	case READ: // Doesn't allow IMM since the argument is necessarily a register
		switch (oper.first & 0x1C) {
		case DIRECT:
			tempOperand = oper.second;
			break;
		case INDIRECT:
			tempOperand = (*m_registers)[oper.second];
			break;
		}
		(*m_registers)[tempOperand] = m_inputTape->read();
		break;
	}

	++m_instructionPointer;
}

void Machine::jumpOps(std::pair<OPCode, int32_t> oper)
{
	switch (oper.first & 0x87) {
	case JUMP:
		m_instructionPointer = oper.second;
		break;

	case JGTZ:
		if (m_registers->getACC() > 0) {
			m_instructionPointer = oper.second;
		} else {
			++m_instructionPointer;
		}

		break;

	case JZERO:
		if (m_registers->getACC() == 0) {
			m_instructionPointer = oper.second;
		} else {
			++m_instructionPointer;
		}

		break;
	}
}

void Machine::debug()
{
	m_instructionPointer = 0;
	m_currentOP = m_program->program()[m_instructionPointer].first;
}

void Machine::step()
{
	if (m_currentOP != HALT) {
		printw("%d %d\n", m_currentOP, m_program->program()[m_instructionPointer].second);
	}

	switch (m_currentOP & 0xE0) {
	case 0x20: // ARITMÉTICAS
		arithmeticOps(m_program->program()[m_instructionPointer]);
		break;

	case 0x40: // REGISTROS
		registerOps(m_program->program()[m_instructionPointer]);
		break;

	case  0x80: // SALTOS
		jumpOps(m_program->program()[m_instructionPointer]);
		break;

	default:
		m_currentOP = HALT;
		break;
	}

	m_currentOP = m_program->program()[m_instructionPointer].first;
}

