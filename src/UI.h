#ifndef UI_H
#define UI_H

#include <stdint.h>

class Machine;

class UI {
public:
	UI(const Machine&);
	~UI();
	void run();

private:
	typedef enum{
	        MENU,
		REGS,
	        TRACE,
	        EXECUTE,
	        DISASSEMBLER,
	        INPUT,
	        OUTPUT,
		HELP
	} Screen;
	
	Machine* m_machine;

	Screen m_screen;
	bool m_running;

	void menu();
	void registers();
	void trace();
	void execute();
	void disassembler();
	void input();
	void output();
	void help();
	void event(int32_t);
};

#endif // UI_H
