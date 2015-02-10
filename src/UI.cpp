#include "UI.h"
#include "RAM/Machine.h"
#include <ncurses.h>
#include <boost/iterator/iterator_concepts.hpp>

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
				m_machine->run();
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
			m_machine->run();
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
		default:
			break;
		}

	} else { //FIXME
		if (ev == static_cast<int32_t>('q')) {
			menu();
		}
		if (m_screen == TRACE) {
			if (ev == static_cast<int32_t>('n')) {
				m_next = true;
			} else if (ev == static_cast<int32_t>('q')) {
				m_next = false;
				menu();
			}
		}
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

void UI::registers() {
	m_screen = REGS;
	
	clear();
	
	attron(A_BOLD);
	printw("Registros\n\n");
	attroff(A_BOLD);
	
	int i = 0;
	for (auto it : m_machine->showRegisters()) {
		printw("R[%d] = %d\n", i++, it);
	}
}

void UI::trace() {
	m_screen = TRACE;
	m_next = true;

	int32_t input;

	clear();
	attron(A_BOLD);
	printw("Traza\n\n");
	attroff(A_BOLD);

	m_machine->debug();
	
	while (m_next) {
		m_machine->step();
		event(getch());
	}
}

void UI::output() {
	m_screen = OUTPUT;
	clear();
	attron(A_BOLD);
	printw("Cinta de salida\n\n");
	attroff(A_BOLD);
	
	for (auto it : m_machine->showOutputTape())
	{
		printw("%d\n", it);
	}
}

void UI::input() {
	m_screen = INPUT;
	clear();
	attron(A_BOLD);
	printw("Cinta de entrada\n\n");
	attroff(A_BOLD);
	
	for (auto it : m_machine->showInputTape()) {
		printw("%d\n", it);
	}
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
	
	int i = 0;
	for (auto it : m_machine->showProgram()) {
		printw("I[%d] ", i++);
		for (auto itt : it) {
			printw("%s ", itt.first.c_str());
		}
		printw("\n");
	}
}

