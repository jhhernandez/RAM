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

#include "ITape.h"
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

ITape::ITape(const char* file) : Tape(file, ios_base::in) {
	fstream ifs(file);
	string str;
	int32_t tmp;
	
	if (ifs.is_open() && ifs.good()) {
		while (!ifs.eof()) {
			getline(ifs, str);
			stringstream ss(str);
			ss >> tmp;
			m_tape.push_back(tmp);
		}
	}
}

ITape::~ITape() {

}

int32_t ITape::read() {
	return m_tape[m_position];
	right();
}
