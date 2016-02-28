/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2016  Juan Hernández Hernández <janukato@gmail.com>
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

#ifndef STRINGSYMBOL_H
#define STRINGSYMBOL_H

#include <string>
#include "../includes.h"

class StringSymbol {
public:
	StringSymbol(const std::string& _str, Symbol _sym);
	const std::string& str() const {
		return m_string;
	}
	
	Symbol sym() const {
		return m_symbol;
	}
private:
	std::string m_string;
	Symbol m_symbol;
};

#endif // STRINGSYMBOL_H
