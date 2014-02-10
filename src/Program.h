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

#ifndef PROGRAM_H
#define PROGRAM_H

#include <string>
#include <vector>
#include <bits/stl_pair.h>
#include <stdint.h>

class Program {
public:
	typedef enum {
		NONE = -1,
		NTS_S = 0,
		NTS_INST,
		NTS_OPERAND,
		TS_MARKER,
		TS_LABEL,
		TS_COMMENT,
		TS_INST_0,
		TS_INST_1_LAB,
		TS_INST_1_OP,
		TS_OP_IMM,
		TS_OP_DIRECT,
		TS_OP_INDIRECT,
	} Symbol;

	typedef enum {
		LOAD,
		STORE,
		READ,
		WRITE,
		ADD,
		SUB,
		MULT,
		DIV,
		JUMP,
		JGTZ,
		JZERO,
		HALT
	} Op;
	/**
	 * \fn CTOR
	 */
	Program();
	/**
	 * \fn DTOR
	 */
	~Program();
	/**
	 * \fn readFile(const char* file)
	 * \param file Ruta del archivo a leer
	 * \return Devuelve 0 en caso de lectura exitosa
	 */
	int32_t readFile(const char*);
	static const std::string symToString(Symbol);
private:
	std::vector<std::vector<std::pair<std::string, Symbol> > > m_program;
	/**
	 * \fn CCTOR
	 */
	Program(const Program& other);
	/**
	 * \fn CCTOR
	 */
	Program& operator=(const Program& other);
	const std::vector<std::pair<std::string, Symbol> > tokenize(const std::string&);
	Program::Symbol lexer(const std::string&);
	int32_t LLparser();
	void showProgram();
	void showTokenizedProgram();
};

#endif // PROGRAM_H
