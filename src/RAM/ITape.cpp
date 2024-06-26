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

using std::string;
using std::fstream;
using std::stringstream;
using std::ios_base;
using std::getline;


ITape::ITape(const string& _file) : Tape(_file, ios_base::in) {
	fstream ifs(_file);
	string str;
	value_t tmp;
	
	if (ifs) {
		while (!ifs.eof()) {
			getline(ifs, str);
			// if the last line in the input file is empty
			// str still has the value of the previous iteration
			// and so it will push it twice
			if (str.empty()) {
				continue;
			}
			
			stringstream ss(str);
			ss >> tmp;
			m_tape.push_back(tmp);
		}
		ifs.close();
	} else {
		throw new FileNotFoundException(_file);
	}
}

ITape::value_t ITape::read() {
	return m_tape[m_position++];
}
