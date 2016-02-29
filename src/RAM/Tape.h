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

#ifndef TAPE_H
#define TAPE_H

#include <vector>
#include <ios>
#include <string>
#include <cstdint>

class FileNotFoundException : public std::exception {
public:
	FileNotFoundException(const std::string& path);
	const char* what() noexcept;
private:
	std::string m_path;
};

class Tape {
private:
	using vector_t = std::vector<int32_t>;

public:
	using size_t = vector_t::size_type;
	using value_t = int32_t;

	Tape(const std::string& _file, std::ios_base::openmode);
	virtual ~Tape() = 0;
	void left();
	void right();
	const vector_t& show() {
		return m_tape;
	}
	
	int32_t operator[](size_t _i) {
		return m_tape[_i];
	}

protected:
	std::string m_file;
	vector_t m_tape;
	size_t m_position;

	value_t read();
	void write(value_t);
};

#endif // TAPE_H
