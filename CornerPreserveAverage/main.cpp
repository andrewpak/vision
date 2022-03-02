#include <iostream>
#include <fstream>
#include <cstdlib>

class imageProcessing {
	
	int numRows, numCols, minVal, maxVal;

	int **frameAry;
	int **outAry;
	int **thrAry;
	int thrVal;
	int mask[8][5][5];

	public:
		imageProcessing(std::ifstream &inFile);
		void loadImage(std::ifstream &inFile);
		void mirrorFraming();
		void setThrVal(int);
		int getThrVal();
		void setNumRows(int);
		void setNumCols(int);
		void setMinVal(int);
		void setMaxVal(int);
		int getNumRows();
		int getNumCols();
		int getMinVal();
		int getMaxVal();
	

		// some helper functions for debugging //

		void check2dAry(int n);
		void destroy1dAry(int *array);
		void destroy2dArys();
};

imageProcessing::imageProcessing(std::ifstream &inFile){
	
	inFile >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;

	std::cout << this->numRows << " " << this->numCols << " " << this->minVal << " " << this->maxVal << std::endl;

	// dynamically allocate arrays //
	
	this->frameAry = new int*[numRows + 4];

	for(int i = 0;i < numRows + 4;i++){
		frameAry[i] = new int[numCols + 4];
	}
	
	this->outAry = new int*[numRows + 4];

	for(int i = 0;i < numRows + 4;i++){
		this->outAry[i] = new int[numCols + 4];
	}

	this->thrAry = new int*[numRows + 4];

	for(int i = 0;i < numRows + 4;i++){
		this->thrAry[i] = new int[numCols + 4];
	}

	/////////////////////////////////
	
	this->loadImage(inFile);
	this->check2dAry(1);
	this->mirrorFraming();
}

void imageProcessing::setThrVal(int n){
	this->thrVal = n;
}

int imageProcessing::getThrVal(){
	return this->thrVal;
}

void imageProcessing::loadImage(std::ifstream &inFile){
	for(int i = 2;i < this->numRows + 2;i++){
		for(int j = 2;j < this->numCols + 2;j++){
			inFile >> frameAry[i][j];
		}
	}		
}

void imageProcessing::mirrorFraming(){
	
	for(int i = 2;i < numCols + 4;i++){
		if(i == 2){
			frameAry[1][i - 1] = frameAry[i][i]; 
			frameAry[0][0] = frameAry[3][3];
			//frameAry[0][1] = frameAry[1][0];
		}
		frameAry[1][i] = frameAry[2][i];
		frameAry[0][i] = frameAry[3][i];
	}

	for(int i = 2;i < numRows + 4;i++){
		if(i == 2){
			frameAry[i - 1][numCols + 2] = frameAry[i][numCols + 1];
			frameAry[1][numCols + 3] = frameAry[1][numCols];
			frameAry[0][numCols + 3] = frameAry[2][numCols - 2];
		}
		frameAry[i][numCols + 2] = frameAry[i][numCols + 1];
		frameAry[i][numCols + 3] = frameAry[i][numCols];
	}

	for(int i = numCols + 2;i > 0;i--){
		frameAry[numRows + 2][i] = frameAry[numRows + 1][i];
		frameAry[numRows + 3][i] = frameAry[numRows][i];
	}

	for(int i = numRows + 2;i > 0;i--){
		frameAry[i][1] = frameAry[i][2];
		frameAry[i][0] = frameAry[i][3]; 
		frameAry[0][1] = frameAry[1][0];
	}

}

///

///
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

void imageProcessing::check2dAry(int n){
	
int arrayNum = n;
if(arrayNum==1){
	std::cout << std::endl;
	for(int i = 0;i < this->numRows + 4;i++){
		for(int j = 0;j < this->numCols + 4;j++){
			if(this->frameAry[i][j] < 10){
				std::cout << this->frameAry[i][j] << "  ";
			} else {
				std::cout << this->frameAry[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}
} else if(arrayNum==2){
	std::cout << std::endl;
	for(int i = 0;i < this->numRows + 4;i++){
		for(int j = 0;j < this->numCols + 4;j++){
			if(this->outAry[i][j] < 10){
				std::cout << this->outAry[i][j] << "  ";
			} else {
				std::cout << this->outAry[i][j] << " ";
			}
		}
		std::cout << std::endl;
		}
	}
	else if(arrayNum==3){
		std::cout << std::endl; 
		for(int i = 0;i < this->numRows + 4;i++){
			for(int j = 0;j < this->numCols + 4;j++){
				if(this->thrAry[i][j] < 10){
					std::cout << this->thrAry[i][j] << "  ";
				} else {
					std::cout << this->thrAry[i][j] << " ";
				}
			}
			std::cout << std::endl;
		}
	}
}

void imageProcessing::destroy1dAry(int *array){
	if(array!=NULL){
		delete [] array;
	}	
}

void imageProcessing::destroy2dArys(){
	if(this->frameAry!=NULL){
		for(int i = 0;i < this->numRows + 4;i++){
			delete this->frameAry[i];
		}
		delete [] this->frameAry;
	}
	
	if(this->outAry!=NULL){
		for(int i = 0;i < this->numRows + 4;i++){
			delete this->outAry[i];
		}
		delete [] this->outAry;
	}
	
	if(this->thrAry!=NULL){
		for(int i = 0;i < this->numRows + 4;i++){
			delete this->thrAry[i];
		}
		delete [] this->thrAry;
	}
}

int main(int argc, char **argv) {
	
	std::string inFileName = argv[1];
	std::ifstream inFile(inFileName);
	std::ofstream outFile1(argv[2]);
	std::ofstream outFile2(argv[3]);
	
	int myThrVal = std::atoi(argv[4]);

	

	imageProcessing myImage(inFile);
	myImage.setThrVal(myThrVal);
	
// checking if arrays are allocated properly cause I'm slow like that //
	
	myImage.check2dAry(1);
//	myImage.check2dAry(2);
//	myImage.check2dAry(3);

	std::cout << std::endl;
  std::cout << myImage.getThrVal() << std::endl;	

///////////////////////////////////////////////////////////////////////




	myImage.destroy2dArys();
	outFile1.close();
	outFile2.close();



	inFile.close();
}
