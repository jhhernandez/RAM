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

#include "../includes.h"

#include <vector>
#include <map>
#include <string>

class Program {
public:
	Program(const std::string& _file);
	
	const std::vector<std::vector<strSymPair> >& programCode() {
		return m_program;
	}
	
	const std::vector<std::pair<OPCode, int32_t> >& program() {
		return m_assembledProgram;
	}
	
	const std::map<std::string, uint32_t>& labels() {
		return m_labels;
	}
private:
	std::vector<std::vector<strSymPair> > m_program;
	std::map<std::string, uint32_t> m_labels;
	std::vector<std::pair<OPCode, int32_t> > m_assembledProgram;
	
	void assemble();
};

#endif // PROGRAM_H
