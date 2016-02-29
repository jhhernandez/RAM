#ifndef UI_H
#define UI_H

#include <stdint.h>

class Machine;

class UI {
public:
	UI(Machine&);
	~UI();
	void run();

private:
	enum class Screen {
	        MENU,
		REGS,
	        TRACE,
	        EXECUTE,
	        DISASSEMBLER,
	        INPUT,
	        OUTPUT,
		HELP
	};
	
	Machine& m_machine;

	Screen m_screen;
	bool m_running;
	bool m_next;

	void menu();
	void registers();
	void trace();
	void disassembler();
	void input();
	void output();
	void help();
	void event(int32_t);
};

#endif // UI_H
