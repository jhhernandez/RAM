#include "UI.h"
#include <ncurses.h>
#include <iostream>

UI::UI() : m_running(false) {
	initscr();
	raw();
	keypad(stdscr, TRUE);
	noecho();
}

UI::~UI() {
	endwin();
}

void UI::run() {
	m_running = true;

	while (m_running) {
		menu();
	}
}

void UI::menu() {
	m_screen = MENU;
	int32_t input;

	clear();
	attron(A_BOLD);
	printw("Máquina RAM\n\n");
	attroff(A_BOLD);
	
	printw("r: ver los registros\n");
	printw("t: traza\n");
	printw("g: go\n");
	printw("s: desensamblador\n");
	printw("i: ver cinta entrada\n");
	printw("o: ver cinta salida\n");
	printw("h: ayuda\n");
	printw("x: salir\n");

	input = getch();

	event(input);
	refresh();
}

void UI::event(int32_t ev) {
	switch (m_screen) {
	case MENU:
		switch (ev) {
		case static_cast<int32_t>('r'):
			break;

		case static_cast<int32_t>('t'):
			break;

		case static_cast<int32_t>('g'):
			break;

		case static_cast<int32_t>('s'):
			break;

		case static_cast<int32_t>('i'):
			break;

		case static_cast<int32_t>('o'):
			break;

		case static_cast<int32_t>('h'):
			break;

		case static_cast<int32_t>('x'):
			m_running = false;
			break;
		}

		break;

	default:
		break;
	}
}

