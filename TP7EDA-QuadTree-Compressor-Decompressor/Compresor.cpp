#include "Compresor.h"
#include <iostream>
Compresor::Compresor(){
	img = nullptr;
	w = 0;
	h = 0;
	threshold = 0;
}


Compresor::~Compresor() {
	free(img);
}


bool Compresor::compress(string file, unsigned int th) {
	threshold = th;
	if (decodeFile(file)) {
		generateCompressedFile(img, w, h, compressdFile);
		outputFile();

		return true;
	}
	else {
		return false;
	}
}

bool Compresor::decodeFile(string file) {

	unsigned char error = lodepng_decode32_file(&img, &w, &h, file.c_str());
	
	if (img == nullptr || error)
		return false;

	return true;

}


void Compresor::generateCompressedFile(unsigned char* img, unsigned int width, unsigned int height, vector<char>& res) {

	squareIteration sqi = iterateSquare(img, width, height);
	
	if (sqi.score <= threshold) {
		res.push_back(0);
		res.push_back(sqi.Rprom);
		res.push_back(sqi.Gprom);
		res.push_back(sqi.Bprom);
		return;
	}

	if (width == 1 || height == 1) {
		res.push_back(0);
		res.push_back(sqi.Rprom);
		res.push_back(sqi.Gprom);
		res.push_back(sqi.Bprom);
		return;
	}

	res.push_back(1);
	generateCompressedFile(img, width / 2, height / 2, res);
	generateCompressedFile(img + 4*(width / 2), width / 2, height / 2, res);
	generateCompressedFile(img + 4 * ((w) * (height / 2)), width / 2, height / 2, res);
	generateCompressedFile(img + 4 * (w * (height / 2) + (width / 2)), width / 2, height / 2, res);
}


squareIteration Compresor::iterateSquare(unsigned char* img, unsigned int w, unsigned int h) {
	
	squareIteration res;

	unsigned char Rmax = 0;
	unsigned char Rmin = 255;
	unsigned char Gmax = 0;
	unsigned char Gmin = 255;
	unsigned char Bmax = 0;
	unsigned char Bmin = 255;

	unsigned long Rprom = 0;
	unsigned long Gprom = 0;
	unsigned long Bprom = 0;
	
	for (int i = 0; i <w; i++) {
		for (int j = 0; j < h; j++) {
			int offset = (j + i * this->w) * 4;

			Rprom += img[offset + RINDEX];
			Gprom += img[offset + GINDEX];
			Bprom += img[offset + BINDEX];

			if (img[offset + RINDEX] > Rmax) {
				Rmax = img[offset + RINDEX];
			}
			else if (img[offset + RINDEX] < Rmin) {
				Rmin = img[offset + RINDEX];
			}

			if (img[offset + GINDEX] > Gmax) {
				Gmax = img[offset + GINDEX];
			}
			else if (img[offset + GINDEX] < Gmin) {
				Gmin = img[offset + GINDEX];
			}

			if (img[offset + BINDEX] > Bmax) {
				Bmax = img[offset + BINDEX];
			}
			else if (img[offset + BINDEX] < Bmin) {
				Bmin = img[offset + BINDEX];
			}
		}
	}

	res.score = Rmax + Gmax + Bmax - Rmin - Gmin - Bmin;
	res.Rprom = Rprom / (w * h);
	res.Gprom= Gprom / (w * h);
	res.Bprom = Bprom / (w * h);

	return res;
}

void Compresor::outputFile() {
	ofstream myfile;
	myfile.open("compressedFile.EDA", ios_base::binary);
	
	saveSize(myfile);
	
	for (auto c : compressdFile) {
		
		myfile << c;
	}
	myfile.close();
}


void Compresor::saveSize(ofstream& myfile) {

	unsigned int* width = &w;
	unsigned char temp;
	temp = *((char*)width);
	myfile << temp;
	temp = *((char*)width + 1);
	myfile << temp;
	temp = *((char*)width + 2);
	myfile << temp;
	temp = *((char*)width + 3);
	myfile << temp;
}
