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
	

		// some helper functions for debugging //

		void check2dAry(int **array, int rows, int cols);
		void destroy1dAry(int *array);
		void destroy2dAry(int **array);
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

// helper functions .. //

void imageProcessing::check2dAry(int **array, int rows, int cols){
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < cols;j++){
			if(array[i][j] < 10){
				std::cout << array[i][j] << "  ";
			} else {
				std::cout <<array[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
}

void imageProcessing::destroy1dAry(int *array){

}

void imageProcessing::destroy2dAry(int **array){

}

int main(int argc, char **argv) {
	
	std::string inFileName = argv[1];
	std::ifstream inFile(inFileName);
	
	imageProcessing myImage(inFile);
	



	inFile.close();
}
