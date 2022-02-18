#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

class Concavity {

	int numRows, numCols, minVal, maxVal;
	int x1, y1, x2, y2;
	int maxHeight;
	int bestThrVal;

	double m;
	double b;

	int *histAry;
	int **displayGraph;

	public:
		Concavity(std::ifstream &inFileHist, std::ifstream &inFilePoints);
		int loadHist(std::ifstream &inFile);
		void dispHist(std::ofstream &outFile);
		int deepestConcavity();
		void plotOneRow(int x, int y);
		void printGraph();
		void printDisplayGraph(std::ofstream &outFile);
		double getM();
		int getX1();
		int getY1();
		int getX2();
		int getY2();
		void setM(double m);
		void setB(double n);
		void setBestThrVal(int n);
		void deleteOneD();
		void deleteTwoD();
		void outPutDisplayGraph();
		void printHistAry();

};


Concavity::Concavity (std::ifstream &inFile, std::ifstream &inFilePoints){
	inFile >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
	std::cout << this->numRows << " " << this->numCols << " " << this->minVal << " " << this->maxVal << std::endl;
	
	inFilePoints >> x1 >> y1 >> x2 >> y2;

	std::cout << std::endl;
	std::cout << this->x1 << " " << this->y1 << " " << this->x2 << " " << this->y2 << std::endl;
	//	dynamically allocate arrays //
	
	histAry = new int[maxVal + 1];
	maxHeight = this->loadHist(inFile);
	std::cout << "this is histAry[i] " << std::endl;
	for(int i = 0;i < maxVal + 1;i++){
		std::cout << histAry[i] << " ";
	}
	std::cout << std::endl;
	
	std::cout << "this is the maxHeight " << maxHeight;
	
	
	/////////////////////////////////////////////////
	
	displayGraph = new int*[maxVal + 1];

	for(int i = 0;i < maxVal + 1;++i){
		displayGraph[i] = new int[maxHeight	+ 1];
	}
	
}

int Concavity::loadHist(std::ifstream &inFile){
	int max = 0;
	for(int i = 0;i < maxVal + 1;i++){
		int index;
		inFile >> index >> this->histAry[i];
		if(histAry[i] > max){
			max = histAry[i];
		}	
		if(inFile.eof()) break;
	}
  return max;
}

void Concavity::dispHist(std::ofstream &outFile){
	outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;

	for(int i = 0;i < maxVal + 1;i++){
		if(histAry[i] == 0) outFile << i << " ( " << 0 << " ):" << std::endl;
		int counter = 0;
		outFile << i << " (  " << histAry[i] <<  " ):";
		while(counter < histAry[i]){
			if(histAry[i] > 70){
				outFile << "+";
				counter++;
			} else {
				outFile << "+";
				counter++;
			}
		}
		counter = 0;
		outFile << std::endl;
	}
}

int Concavity::deepestConcavity(){
	std::cout << "printing values of histAry in deepestConcavity " << std::endl;
	for(int i = 0;i < maxVal + 1;i++){
		std::cout << histAry[i] << " ";
	}

	int max = 0;
	std::cout << "this is x1 " << this->x1 << " this is x2 " << this->x2 << std::endl;
	int first = this->x1;
 	int second = this->x2;
  int x = first;
	int thr = first;
	
	std::cout << "this is max: " << max << " this is first: " << first << " this is second: " << second << std::endl;
	while(x <= second){
	std::cout << "this is m " << m << std::endl;
	int y = (int) (this->m * x + this->b);
	std::cout << "this is y " << y << std::endl;
	this->plotOneRow(x, y);
	std::cout << "this is x " << x << std::endl;
	std::cout << "this is histAry[x] " << histAry[x] << std::endl;
	int gap = std::abs( (this->histAry[x] - y) );
	std::cout << "this is gap: " << gap << " and this is max " << max << std::endl;
	if(gap > max){
		std::cout << "we are in the gap > max condition..." << std::endl;
		max = gap;
		thr = x;

		std::cout << "the max is now " << max << " the thr is now " << thr << std::endl;
	}
	x++;
	}
	std::cout << "this is thr " << thr << std::endl;
	return thr;


}

void Concavity::plotOneRow(int x, int y){
	int index = std::min(histAry[x], y);
	int last = std::max(histAry[x], y);
 	std::cout << "this is index " << index << " this is last " << last << std::endl;
	while(index <= last){
	this->displayGraph[x][index] = 3;
		index++;
	}
	displayGraph[x][this->histAry[x]] = 1;
	displayGraph[x][last] = 2;
}

void Concavity::printDisplayGraph(std::ofstream &outFile){
	outFile << std::endl;
	outFile << "The best threshold value is " << this->bestThrVal;
	for(int i = 0;i < maxVal + 1;i++){
		for(int j = 0;j < maxHeight + 1;j++){
			if(displayGraph[i][j] == 0){
				outFile << " ";
			} 
			else if(displayGraph[i][j] == 1){
				outFile << "*";
			}
			else if(displayGraph[i][j] == 2){
				outFile << "+";
			}
			else if(displayGraph[i][j] == 3){
				outFile << "=";
			}
		}
		outFile << std::endl;
	}

}

double Concavity::getM(){
	return this->m;
}

int Concavity::getX1(){
	return this->x1;
}

int Concavity::getY1(){
	return this->y1;
}

int Concavity::getX2(){
	return this->x2;
}

int Concavity::getY2(){
	return this->y2;
}

void Concavity::setM(double n){
	this->m = n;
}

void Concavity::setB(double n){
	this->b = n;
}

void Concavity::setBestThrVal(int n){
	this->bestThrVal = n;
}

void Concavity::deleteOneD(){
	if(this->histAry!=NULL){
		delete [] histAry;
	}
}

void Concavity::deleteTwoD(){
	if(this->displayGraph!=NULL){
		for(int i = 0;i < maxVal + 1;i++){
			delete [] displayGraph[i];
		}
		delete [] displayGraph;
	}
}

// I made the following functions for debugging reasons
void Concavity::outPutDisplayGraph(){
	for(int i = 0;i < maxVal + 1;i++){
		for(int j = 0;j < maxHeight + 1;j++){	
			std::cout << this->displayGraph[i][j] << " ";
		}
		std::cout << std::endl;
	}
}

void Concavity::printHistAry(){
	std::cout << "printing HistAry...." << std::endl;
	for(int i = 0;i < maxVal + 1;i++){
		std::cout << histAry[i] <<  " ";
	}
}

int main(int argc, char **argv){
	
	std::string fileNameHist = argv[1];
	std::string fileNamePoints = argv[2];
	std::ifstream fileHist(fileNameHist);
	std::ifstream filePoints(fileNamePoints);
	Concavity myHist(fileHist, filePoints);
	std::string outFile1Name = argv[3];
	std::ofstream outFile(outFile1Name);
	
	myHist.dispHist(outFile);
	
	myHist.setM((double) (myHist.getY2() - myHist.getY1()) / (double) (myHist.getX2() - myHist.getX1()));
	std::cout << '\n' << myHist.getM() << std::endl;
	myHist.setB((double) myHist.getY1() - (myHist.getM() * (double)  myHist.getX1()));	
	myHist.setBestThrVal(myHist.deepestConcavity());
  myHist.outPutDisplayGraph();	
	myHist.printDisplayGraph(outFile);
	myHist.printHistAry();
	myHist.deleteOneD();
	myHist.deleteTwoD();
	fileHist.close();
  filePoints.close();
	outFile.close();

}

