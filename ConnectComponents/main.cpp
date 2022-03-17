#include<iostream>
#include<cstdlib>
#include<string>
#include<fstream>
#include<cmath>
class ConnectComponents {

	private:
		int numRows, numCols, minVal, maxVal;
		int newMin, newMax, newLabel;
		int trueNumCC;
		int **zeroFramedAry;
		int NonZeroNeighborAry[5];

		int *EQAry;

	public:
		ConnectComponents(std::ifstream &inFile);
		void setNumRows(int n);
		void setNumCols(int n);
		int getNumRows();
		int getNumCols();
		void setNewLabel(int n);
		void delete2DAry(int **array);
		int** getZeroFramed();
		void setZeroFramed(int rows, int cols);
		void print2DAry(int** array, int rows, int cols);
		void loadImg(std::ifstream &inFile, int** array);
		void connect4Pass1();
};

ConnectComponents::ConnectComponents(std::ifstream &inFile){
	
	inFile >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;  	

	std::cout << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
}


void ConnectComponents::loadImg(std::ifstream &inFile, int** array){
	for(int i = 1;i <= numRows;i++){
		for(int j = 1;j <= numCols;j++){
			inFile >> array[i][j];
		}
	}
}

void ConnectComponents::connect4pass1(){
	for(int i = 1;i <= numRows;i++){
		for(int j = 1;j <= numCols;j++){
			if(zeroFramedAry[i][j] > 0){
				nonZeroNeighborAry[0] = zeroFramedAry[i - 1][j];
				nonZeroNeighborAry[1] = zerFramedAry[i][j -1];
					
				if(nonZeroNeighborAry[0] == 0 && nonZeroNeighborAry[1] == 0){
					newLabel++;
					zeroFramedAry[i][j] == newLabel;
				}
				else if(zeroFramedAry[i][j]){
					std::min(nonZeroNeighborAry[0], nonZeroNeighborAry[1]); 
				}
				

			}
		}
	}	
}



void ConnectComponents::setNumRows(int n){
	this->numRows = n;
}

void ConnectComponents::setNumCols(int n){
	this->numCols = n;
}

int ConnectComponents::getNumRows(){
	return this->numRows;
}


int ConnectComponents::getNumCols(){
	return this->numCols;
}

void ConnectComponents::setNewLabel(int n){
	this->newLabel = n;
}

void ConnectComponents::setZeroFramed(int rows, int cols){
	zeroFramedAry = new int*[rows];
	for(int i = 0;i < rows;i++){
		zeroFramedAry[i] = new int[cols];
	}
}

void ConnectComponents::delete2DAry(int **array){
	for(int i = 0;i < this->numRows + 2;i++){
		delete array[i];
	}
	delete [] array;
}

int** ConnectComponents::getZeroFramed(){
	return zeroFramedAry;
}

void ConnectComponents::print2DAry(int** array, int rows, int cols){
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < cols;j++){
			std::cout << array[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

int main(int argc, char **argv){
	
	std::cout << "starting connect components" << std::endl;

	std::ifstream inFile(argv[1]);
	ConnectComponents myConnect(inFile);	
	
	std::ofstream RFprettyPrintFile(argv[2]);

	std::ofstream labelFile(argv[3]);
	std::ofstream propertyFile(argv[4]);
	
	myConnect.setNewLabel(0);
	
	myConnect.setZeroFramed(myConnect.getNumRows() + 2, myConnect.getNumCols() + 2);
	myConnect.print2DAry(myConnect.getZeroFramed(), myConnect.getNumRows() + 2, myConnect.getNumCols() + 2);
	myConnect.loadImg(inFile, myConnect.getZeroFramed());
	
	std::cout << std::endl;
	myConnect.print2DAry(myConnect.getZeroFramed(), myConnect.getNumRows() + 2, myConnect.getNumCols() + 2);
	int Connectness = 0;
	std::cout << std::endl;
	
	while(Connectness != 4 && Connectness != 8){	
		std::cout << "Please insert the number of Connectness: " << std::endl;
		std::cin >> Connectness;
	}

	std::cout << std::endl;
	std::cout << Connectness << std::endl;
	
	if(Connectness == 4){

	}
	else if(Connectness == 8){

	}
	else {

	}


	RFprettyPrintFile.close();
	labelFile.close();
	propertyFile.close();

}
