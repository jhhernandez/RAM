#include "src/RAM/Machine.h"
#include "src/UI.h"

#include <iostream>

using namespace std;

int main(int argc, char** argv) {
	if (argc < 4) {
		cout << "Usage: ram program.ram input.tape output.tape" << endl;
		return 0;
	}
	Machine m(argv[1], argv[2], argv[3]);

	UI ui(m);
	ui.run();
}

/*
 * Especificaciones:

	Los programas a cargar en la máquina RAM y los contenidos de las cintas de entrada y de salida deben estar en tres ficheros diferentes, y sus nombres deben poder ser introducidos mediante teclado.
	Deben leerse la instrucciones desde el programa y chequear que sean legales. La instrucciones deben ser implementadas con los direccionamientos permitidos.
	Deben chequearse los desbordamientos en sumas restas y multiplicaciones tanto positivos como negativos. Chequéese que no se intente realizar una división por cero.
	Ante alguno de los errores anteriores se debe imprimir por pantalla un mensaje y la posición de memoria de la instrucción que lo produjo y dejar la máquina RAM en estado halt.
	Cuando se entra en estado halt se debe descargar el contenido de la cinta de salida en el fichero correspondiente.
*/