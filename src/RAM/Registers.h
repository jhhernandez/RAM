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

#ifndef REGISTERS_H
#define REGISTERS_H

#include <vector>
#include <cstdint>
#include <cstddef>

class Registers {
public:
	Registers();

	const std::vector<int32_t>& show() {
		return m_register;
	}

	void setACC(int32_t);
	
	// FIXME: -Wreturn-type. throw outofrange
	int32_t& operator[](uint32_t pos) {
		if (pos >= 1 && pos < m_size) {
			return m_register[pos];
		}
	}

	int32_t getACC() {
		return m_register[0];
	}
private:
	std::vector<int32_t> m_register;
	static const size_t m_size = 10;
};

#endif // REGISTERS_H
