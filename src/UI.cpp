#include "UI.h"
#include "RAM/Machine.h"
#include <ncurses.h>

using namespace std;

UI::UI(const Machine& machine) : m_machine(const_cast<Machine*>(&machine)), m_running(false), m_screen(MENU) {
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
		switch (m_screen) {
			case MENU:
				menu();
				break;
			case REGS:
				break;
			case TRACE:
				trace();
				break;
			case EXECUTE:
				execute();
				break;
			case DISASSEMBLER:
				disassembler();
				break;
			case INPUT:
				input();
				break;
			case OUTPUT:
				output();
				break;
			case HELP:
				help();
				break;
		}
		
		event(getch());
		refresh();
	}
}

void UI::menu() {
	m_screen = MENU;

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
}

void UI::event(int32_t ev) {
	
	if (m_screen == MENU) {
		switch (ev) {
		case static_cast<int32_t>('r'):
			registers();
			break;

		case static_cast<int32_t>('t'):
			trace();
			break;

		case static_cast<int32_t>('g'):
			execute();
			break;

		case static_cast<int32_t>('s'):
			disassembler();
			break;

		case static_cast<int32_t>('i'):
			input();
			break;

		case static_cast<int32_t>('o'):
			output();
			break;

		case static_cast<int32_t>('h'):
			help();
			break;

		case static_cast<int32_t>('x'):
			m_running = false;
			break;
		}

	} else {
		if (ev == static_cast<int32_t>('q')) {
			menu();
		}
	}
}

void UI::registers() {
	m_screen = REGS;
	
	clear();
	
	attron(A_BOLD);
	printw("Registros\n\n");
	attroff(A_BOLD);
	
	for (vector<int32_t>::const_iterator i = m_machine->showRegisters().begin();
	     i != m_machine->showRegisters().end(); ++i) {
		printw("R[%d]\n", (*i));
	}
}

void UI::trace() {
	m_screen = TRACE;

	clear();
	attron(A_BOLD);
	printw("Traza\n\n");
	attroff(A_BOLD);
}

void UI::output() {
	m_screen = OUTPUT;
}

void UI::execute() {
	m_screen = EXECUTE;
}

void UI::input() {
	m_screen = INPUT;
}

void UI::help() {
	m_screen = HELP;
	
	clear();
	attron(A_BOLD);
	printw("Ayuda\n");
	attroff(A_BOLD);
	
	printw("Para salir de cualquier subpantalla pulsar q\n");
}

void UI::disassembler() {
	m_screen = DISASSEMBLER;
	
	clear();
	
	for (vector<vector<strSymPair> >::const_iterator i = m_machine->showProgram().begin();
	     i != m_machine->showProgram().end(); ++i) {
		printw("I[%d] ", i - m_machine->showProgram().begin());
		for (vector<strSymPair>::const_iterator j = (*i).begin();
		     j != (*i).end(); ++j) {
			printw("%s ", (*j).first.c_str());
		}
		printw("\n");
	}
}

