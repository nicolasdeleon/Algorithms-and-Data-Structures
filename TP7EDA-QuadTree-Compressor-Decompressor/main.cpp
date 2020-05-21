#include <iostream>
#include "Compresor.h"
#include "Descompresor.h"

int main(void) {

	Compresor c;

	if (c.compress("imagenfuego.png", 10))
		cout << "Compressed OK" << endl;
	else
		cout << "FAILED" << endl;

	Descompresor desc;
	
	if (desc.decompress("compressedFile.EDA"))
		cout << "Decompressed OK" << endl;
	else
		cout << "FAILED" << endl;

	return 0;
}
