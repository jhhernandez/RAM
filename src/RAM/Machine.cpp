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

using std::string;

Machine::Machine(const string& _program, const string& _input, const string& _output) :
	m_program(_program), m_inputTape(_input), m_outputTape(_output)
{
}

uint32_t Machine::run()
{
	m_instructionPointer = 0;

	m_currentOP = m_program.program()[m_instructionPointer].first;

	while (m_currentOP != OPCode::HALT) {
		m_currentOP = m_program.program()[m_instructionPointer].first;

		switch (m_currentOP & OPMask::TYPE) {
		case ARITHMETIC:
			arithmeticOps(m_program.program()[m_instructionPointer]);
			break;

		case REGISTER:
			registerOps(m_program.program()[m_instructionPointer]);
			break;

		case  BRANCH:
			jumpOps(m_program.program()[m_instructionPointer]);
			break;

		default:
			m_currentOP = OPCode::HALT;
			break;
		}
	}

	m_outputTape.save();
	return 0;


	return -1;
}

void Machine::arithmeticOps(std::pair<OPCode, int32_t> oper)
{
	int32_t tempOperand;

	switch (oper.first & OPMask::REDIRECTION) {
	case OPCode::IMM:
		tempOperand = oper.second;
		break;

	case OPCode::DIRECT:
		tempOperand = m_registers[oper.second];
		break;

	case OPCode::INDIRECT:
		tempOperand = m_registers[m_registers[oper.second]];
		break;

	default:
		break;
	}

	switch (oper.first & OPMask::OPERATION) {
	case OPCode::ADD:
		if (m_registers.getACC() + tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers.getACC() + tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = OPCode::HALT;
			return;
		}

		m_registers.setACC(m_registers.getACC() + tempOperand);
		break;

	case OPCode::SUB:
		if (m_registers.getACC() - tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers.getACC() - tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = OPCode::HALT;
			return;
		}

		m_registers.setACC(m_registers.getACC() - tempOperand);
		break;

	case OPCode::MULT:
		if (m_registers.getACC() * tempOperand > OPERAND_UPPER_BOUND ||
		        m_registers.getACC() * tempOperand < OPERAND_LOWER_BOUND) {
			m_machineState = OVERFLOW;
			m_currentOP = OPCode::HALT;
			return;
		}

		m_registers.setACC(m_registers.getACC() * tempOperand);
		break;

	case OPCode::DIV:
		if (tempOperand == 0) {
			m_machineState = ZERO_DIV;
			m_currentOP = OPCode::HALT;
			return;
		} else {
			m_registers.setACC(m_registers.getACC() / tempOperand);
		}

		break;

	default:
		break;
	}

	++m_instructionPointer;
}

void Machine::registerOps(std::pair<OPCode, int32_t> oper)
{
	int32_t tempOperand;
	//printw("%d\n", oper.first);

	switch (oper.first & OPMask::REDIRECTION) {
	case OPCode::IMM:
		tempOperand = oper.second;
		break;

	case OPCode::DIRECT:
		tempOperand = m_registers[oper.second];
		break;

	case OPCode::INDIRECT:
		tempOperand = m_registers[m_registers[oper.second]];
		break;

	default:
		break;
	}

	switch (oper.first & OPMask::REGISTER) {
	case OPCode::LOAD: // Allows IMM, DIRECT and INDIRECT
		m_registers.setACC(tempOperand);
		break;

	case OPCode::WRITE: // Allows IMM, DIRECT and INDIRECT
		m_outputTape.write(tempOperand);
		break;

	case OPCode::STORE: // Doesn't allow IMM since the argument is necessarily a register
		switch (oper.first & OPMask::REDIRECTION) {
		case OPCode::DIRECT:
			tempOperand = oper.second;
			break;

		case OPCode::INDIRECT:
			tempOperand = m_registers[oper.second];
			break;

		default:
			break;
		}

		m_registers[tempOperand] = m_registers.getACC();
		break;

	case OPCode::READ: // Doesn't allow IMM since the argument is necessarily a register
		switch (oper.first & OPMask::REDIRECTION) {
		case OPCode::DIRECT:
			tempOperand = oper.second;
			break;

		case OPCode::INDIRECT:
			tempOperand = m_registers[oper.second];
			break;

		default:
			break;
		}

		m_registers[tempOperand] = m_inputTape.read();
		break;

	default:
		break;
	}

	++m_instructionPointer;
}

void Machine::jumpOps(std::pair<OPCode, int32_t> oper)
{
	switch (oper.first & OPMask::BRANCH) {
	case OPCode::JUMP:
		m_instructionPointer = oper.second;
		break;

	case OPCode::JGTZ:
		if (m_registers.getACC() > 0) {
			m_instructionPointer = oper.second;
		} else {
			++m_instructionPointer;
		}

		break;

	case OPCode::JZERO:
		if (m_registers.getACC() == 0) {
			m_instructionPointer = oper.second;
		} else {
			++m_instructionPointer;
		}

		break;

	default:
		break;
	}
}

void Machine::debug()
{
	m_instructionPointer = 0;
	m_currentOP = m_program.program()[m_instructionPointer].first;
}

void Machine::step()
{
	if (m_currentOP != OPCode::HALT) {
		printw("%d %d\n", m_currentOP, m_program.program()[m_instructionPointer].second);
	}

	switch (m_currentOP & OPMask::TYPE) {
	case ARITHMETIC:
		arithmeticOps(m_program.program()[m_instructionPointer]);
		break;

	case REGISTER:
		registerOps(m_program.program()[m_instructionPointer]);
		break;

	case  BRANCH:
		jumpOps(m_program.program()[m_instructionPointer]);
		break;

	default:
		m_currentOP = OPCode::HALT;
		break;
	}

	m_currentOP = m_program.program()[m_instructionPointer].first;
}

