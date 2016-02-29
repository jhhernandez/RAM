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

#include "Tape.h"

using std::string;
using std::ios_base;

FileNotFoundException::FileNotFoundException(const std::string& path) : m_path(path) {
	
}

const char* FileNotFoundException::what() noexcept
{
	return m_path.c_str();
}

Tape::Tape(const string& _file, ios_base::openmode mode) : m_file(_file), m_position(0) {
}

Tape::~Tape() {

}

void Tape::left() {
	if (m_position > 0) {
		--m_position;
	} else {
		m_position = m_tape.size() - 1;
	}
}

void Tape::right() {
	if (m_position < m_tape.size()) {
		++m_position;
	} else {
		m_position = 0;
	}
}
