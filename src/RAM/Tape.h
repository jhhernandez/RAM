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
	FileNotFoundException(const char* path);
	const char* what() noexcept;
private:
	const char* m_path;
};

class Tape {
public:
	Tape(const std::string& _file, std::ios_base::openmode);
	virtual ~Tape() = 0;
	void left();
	void right();
	const std::vector<int32_t>& show() {
		return m_tape;
	}

protected:
	std::string m_file;
	std::vector<int32_t> m_tape;
	uint32_t m_position;

	int32_t read();
	void write(int32_t);
};

#endif // TAPE_H
