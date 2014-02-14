#include "src/Program.h"

#include <iostream>

using namespace std;

int main(int argc, char **argv) {
	Program p("../test/test2.ram");

    p.showTokenizedProgram();
}
