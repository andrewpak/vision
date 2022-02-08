#include <iostream>
#include <fstream>

int main(int argc, char *argv[]){
	
	std::ifstream inFile(argv[1]);

	int numRows, numCols, minVal, maxVal;
	 
	inFile >> numRows >> numCols >> minVal >> maxVal;

	std::cout << "this is numRows: " << numRows << std::endl;
	std::cout << "this is numCols: " << numCols << std::endl;
	std::cout << "this is minVal: " << minVal << std::endl;
	std::cout << "this is maxVal: " << maxVal << std::endl;

	int histAry[maxVal + 1];
	for(int i = 0;i < maxVal + 1;i++){

		histAry[i] = 0;

	}

	for(int i = 0;i < maxVal + 1;i++){
		std::cout<< histAry[i] << " ";
	}

	int image[numRows][numCols];

	for(int i = 0;i < numRows;i++){
		for(int j = 0;j < numCols;j++){
			inFile >> image[i][j];
		}
	}
		std::cout<< std::endl;
	for(int i = 0;i < numRows;i++){
		for(int j = 0;j < numCols;j++){
			std::cout << image[i][j] << " ";
		}
		std::cout << std::endl;
	}

	for(int i = 0;i < numRows;i++){
		for(int j = 0;j < numCols;j++){
				histAry[image[i][j]]++;
		}
	}
	std::cout << "This is the histAry: " << std::endl;
	for(int i = 0;i <= maxVal;i++){
		std::cout << histAry[i] << " ";
	}




}
