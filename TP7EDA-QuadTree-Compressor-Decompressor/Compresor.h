#pragma once
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>

#include "lodepng.h"

using namespace std;

typedef struct {
	unsigned int score;
	unsigned char Rprom;
	unsigned char Gprom;
	unsigned char Bprom;
} squareIteration;

class Compresor {

	enum {
		RINDEX,
		GINDEX,
		BINDEX
	};

public:
	
	Compresor();
	~Compresor();
	
	bool compress(string file, unsigned int th);
	void saveSize(std::ofstream& myfile);

private:

	bool decodeFile(string file);
	void generateCompressedFile(unsigned char* img, unsigned int w, unsigned int h, vector<char>& res);
	squareIteration iterateSquare(unsigned char* img, unsigned int w, unsigned int h);
	void outputFile();
	unsigned char* img;
	unsigned int w, h;
	vector<char> compressdFile;
	unsigned int threshold;
};