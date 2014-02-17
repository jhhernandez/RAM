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

#include "OTape.h"
#include <fstream>

using namespace std;

OTape::OTape(const char* file) : Tape(file, ios_base::out) {
}


OTape::~OTape() {

}

void OTape::write(int32_t val) {
	m_tape.resize(m_tape.size() + 1);
	m_tape[m_position] = val;
	right();
}

void OTape::save() {
	fstream ofs(m_file.c_str());
	if (ofs.is_open() && ofs.good()) {
		for (vector<int32_t>::iterator i = m_tape.begin(); i != m_tape.end(); ++i) {
			ofs << (*i);
		}
	}
}
