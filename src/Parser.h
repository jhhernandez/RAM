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

#ifndef PARSER_H
#define PARSER_H

#include "includes.h"

#include <vector>

class Parser {
public:
	/**
	 * \fn CTOR
	 */
	Parser();
	/**
	 * \fn DTOR
	 */
	~Parser();
	/**
	 * \fn readFile(const char* file)
	 * \param file Ruta del archivo a leer
	 * \return Devuelve 0 en caso de lectura exitosa
	 */
	int32_t readFile(const char*);
	/**
	 * \fn parse()
	 * \return 0 si el parseo se completa
	 */
	int32_t parse();
	std::vector<std::vector<strSymPair> > program() {
		return m_program;
	}
private:
	std::vector<std::vector<strSymPair> > m_program;
	/**
	 * \fn CCTOR
	 */
	Parser(const Parser& other);
	/**
	 * \fn CCTOR
	 */
	Parser& operator=(const Parser& other);
	const std::vector<strSymPair> tokenize(const std::string&);
	Symbol lexer(const std::string&);
};

#endif // PROGRAM_H