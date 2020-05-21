#include "Descompresor.h"

Descompresor::Descompresor() {
	w = 0;
	img = nullptr;
}
Descompresor::~Descompresor() {

}

bool Descompresor::loadFile(const char* filename) {

	ifstream file;
	file.open(filename, ios_base::binary);

	w = getSize(file);
	
	fileData.resize(w * w * 4);
	
	char c = 0;
	while (file.get(c))
		decompressedList.push_back(c);

	return true;
}

bool Descompresor::decompress(const char* file) {
	bool result = true;
	loadFile(file);
	generateImage(0, w);
	result = output();

	return result;
}

void Descompresor::generateImage(unsigned int pos, unsigned int side) {

	if (side == 0) {
		return;
	}
	
	

	//unsigned char value = decompressdFile.front();
	//decompressdFile.erase(decompressdFile.begin());
	unsigned char value = decompressedList.front();
	decompressedList.pop_front();

	if (value == 0) {
		unsigned char red = decompressedList.front();
		decompressedList.pop_front();
		unsigned char green = decompressedList.front();
		decompressedList.pop_front();
		unsigned char blue = decompressedList.front();
		decompressedList.pop_front();
		writeData(pos, side, red, green, blue);
		return;

	} else if (value == 1) {
		generateImage(pos, side / 2);
		generateImage(pos + 4 * (side / 2), side / 2);
		generateImage(pos + 4 * (w * (side / 2)), side / 2);
		generateImage(pos + 4 * (w * (side / 2) + (side / 2)), side / 2);
	}
}

void Descompresor::writeData(unsigned int pos, unsigned int side, unsigned char red, unsigned char green ,unsigned char blue) {

	unsigned int i;
	for (i = 0; i <side; i++) {
		for (int j = 0; j < side; j++) {
			int offset = (j + i * w) * 4;
			fileData[pos + offset] = red;
			fileData[pos + offset + 1] = green;
			fileData[pos + offset + 2] = blue;
			fileData[pos + offset + 3] = ALPHA;
		}
	}
}

bool Descompresor::output() {
	bool result = true;
	unsigned char error = lodepng_encode32_file("imagenNueva.png", fileData.data(), w, w);
	if (error)
		result = false;

	return result;
}

int Descompresor::getSize(ifstream& file) {

	char c = 0;
	file.get(c);
	char size[4];
	size[0] = c;
	file.get(c);
	size[1] = c;
	file.get(c);
	size[2] = c;
	file.get(c);
	size[3] = c;
	int tam = *((int*)size);

	return tam;
}