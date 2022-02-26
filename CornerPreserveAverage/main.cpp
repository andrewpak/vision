#include <iostream>
#include <fstream>
#include <cstdlib>

class imageProcessing {
	
	int numRows, numCols, minVal, maxVal;

	int **framAry;
	int **outAry;
	int **thrAry;
	int thrVal;
	int mask[8][5][5];

	public:
		imageProcessing(std::ifstream &inFile);
		void setNumRows(int);
		void setNumCols(int);
		void setMinVal(int);
		void setMaxVal(int);
		int getNumRows();
		int getNumCols();
		int getMinVal();
		int getMaxVal();

};

imageProcessing::imageProcessing(std::ifstream &inFile){
	
	inFile >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;

	std::cout << this->numRows << " " << this->numCols << " " << this->minVal << " " << this->maxVal << std::endl;
}

void imageProcessing::setNumRows(int n){
	this->numRows = n;
}

void imageProcessing::setNumCols(int n){
	this->numCols = n;
}

void imageProcessing::setMinVal(int n){
	this->minVal = n;
}

void imageProcessing::setMaxVal(int n){
	this->maxVal = n;
}

int imageProcessing::getNumRows(){
	return this->numRows;
}

int imageProcessing::getNumCols(){
	return this->numCols;
}

int imageProcessing::getMinVal(){
	return this->minVal;
}

int imageProcessing::getMaxVal(){
	return this->maxVal;
}

int main(int argc, char **argv) {
	
	std::string inFileName = argv[1];
	std::ifstream inFile(inFileName);
	
	imageProcessing myImage(inFile);
	



	inFile.close();
}
