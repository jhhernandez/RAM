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

class Program {
private:
	typedef enum {
		NTS_S = 0,
		NTS_A,
		NTS_B,
		NTS_C,
		NTS_D,
		NTS_E,
		TS_LABEL,
		TS_INS,
		TS_OPER,
		TS_COMMENT,
		TS_EOS
	} Symbol;
	/**
	 * \fn CCTOR
	 */
	Program(const Program& other);
	/**
	 * \fn CCTOR
	 */
	Program& operator=(const Program& other);
	Program::Symbol lexer(const char*);
	int parser();
public:
	/**
	 * \fn CTOR
	 */
	Program();
	/**
	 * \fn DTOR
	 */
	~Program();
	/**
	 * \fn readFile(const char* file)
	 * \param file Ruta del archivo a leer
	 * \return Devuelve 0 en caso de lectura exitosa
	 */
	int readFile(const char*);
};

#endif // PROGRAM_H
