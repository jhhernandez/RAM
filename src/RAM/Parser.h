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

#include "StringSymbol.h"
#include "../includes.h"

#include <vector>
#include <map>
#include <string>

class Parser {
public:
	/**
	 * \fn CTOR
	 */
	Parser(const std::string& _file);

	const std::vector<std::vector<StringSymbol>>& program() {
		return m_program;
	}

	const std::map<std::string, uint32_t>& labels() {
		return m_labels;
	}

private:
	std::vector<std::vector<StringSymbol>> m_program;
	std::map<std::string, uint32_t> m_labels;

	const std::vector<StringSymbol> tokenize(const std::string&);
	Symbol lexer(const std::string&);

	/**
	 * \fn readFile(const std::string& file)
	 * \param file Ruta del archivo a leer
	 * \return Devuelve 0 en caso de lectura exitosa
	 */
	int32_t readFile(const std::string& _file);

	/**
	* \fn parse()
	* \return 0 si el parseo se completa
	*/
	int32_t parse(const std::vector<std::vector<StringSymbol>>& _program);
};

#endif // PROGRAM_H
