#ifndef UI_H
#define UI_H

#include <stdint.h>

class UI {
public:
	UI();
	~UI();
	void run();

private:
	typedef enum{
	        MENU,
	        TRACE,
	        EXECUTE,
	        DISASSEMBLER,
	        INPUT,
	        OUTPUT
	} Screen;

	Screen m_screen;
	bool m_running;

	void menu();
	void trace();
	void execute();
	void disassembler();
	void input();
	void output();
	void help();
	void event(int32_t);
};

#endif // UI_H
