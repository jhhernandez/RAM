#include "src/RAM/Machine.h"
#include "src/UI.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	Machine m;
	m.programFile("../test/test3.ram");
	//m.inputFile("../tape");
	//m.outputFile("../tape");
	
	UI ui(m);
	ui.run();
}

/*
 * En esta segunda práctica se trata de finalizar el desarrollo del simulador de programas RAM.  El programa debe estar escrito en C++ utilizando Orientación a Objetos.

Especificaciones:

Los programas a cargar en la máquina RAM y los contenidos de las cintas de entrada y de salida deben estar en tres ficheros diferentes, y sus nombres deben poder ser introducidos mediante teclado. Deben leerse la instrucciones desde el programa y chequear que sean legales. La instrucciones deben ser implementadas con los direccionamientos permitidos. Deben chequearse los desbordamientos en sumas restas y multiplicaciones tanto positivos como negativos. Chequéese que no se intente realizar una división por cero. Ante alguno de los errores anteriores se debe imprimir por pantalla un mensaje y la posición de memoria de la instrucción que lo produjo y dejar la máquina RAM en estado halt.
Cuando se entra en estado halt se debe descargar el contenido de la cinta de salida en el fichero correspondiente.

Debe presentarse un menú de ejecución similar al siguiente:

>h
r: ver los registros
t: traza
g: go
s: desensamblador
i: ver cinta entrada
o: ver cinta salida
h: ayuda
x: salir
>*/