#include "src/Program.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Program p;
	if (p.readFile("../test/test2.ram") < 0) {
		cout << "ERROR" << endl;
	}
}
