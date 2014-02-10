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
#include <stdint.h>

class Program {
public:
	typedef enum {
	        NONE = -1,
	        NTS_S = 0,
	        NTS_INST,
	        NTS_MARKER_INST,
	        NTS_MARKER_COMMENT,
	        NTS_INST_COMMENT,
	        NTS_MARKER_INST_COMMENT,
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
	/**
	 * \fn CCTOR
	 */
	Program(const Program& other);
	/**
	 * \fn CCTOR
	 */
	Program& operator=(const Program& other);
	const std::vector<std::string> tokenize(const std::string&);
	Program::Symbol lexer(const std::string&);
	int32_t LLparser(const std::vector<std::vector<std::string> >&);
};

#endif // PROGRAM_H
