#include <iostream>
#include <fstream>
#include <string>


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
		int loadHist();
		void dispHist(std::ofstream &outFile);
		int deepestConcavity();
		void plotOneRow();
		void printGraph();
		double getM();
		int getX1();
		int getY1();
		int getX2();
		int getY2();
		void setM(double m);
};


Concavity::Concavity (std::ifstream &inFile, std::ifstream &inFilePoints){
	inFile >> this->numRows >> this->numCols >> this->minVal >> this->maxVal;
	std::cout << this->numRows << " " << this->numCols << " " << this->minVal << " " << this->maxVal << std::endl;
	
	inFilePoints >> x1 >> y1 >> x2 >> y2;

	std::cout << std::endl;
	std::cout << this->x1 << " " << this->y1 << " " << this->x2 << " " << this->y2 << std::endl;
	//	dynamically allocate arrays //
	
	this->histAry = new int[maxVal + 1];
	
	for(int i = 0;i < maxVal + 1;i++){
		std::cout << histAry[i] << " ";
	}
	std::cout << std::endl;	
	for(int i = 0;i < maxVal + 1;i++){
		int index;
		inFile >> index >> histAry[i];
		if(inFile.eof()) break;
	}
	for(int i = 0;i < maxVal + 1;i++){
		std:: cout << histAry[i] << " ";
	}
	//////////////////////////////////
	
	
}

void Concavity::dispHist(std::ofstream &outfile){
	outfile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
 
  for(int i = 0;i < maxVal + 1; i++){
    if (this->histAry[i] == 0) outfile << i << " (  " << 0 << "  ):" << std::endl;
      while(this->histAry[i] > 0){

        if(this->histAry[i] > 70){
          outfile << i << " (  " << 70 << " ):";
          for(int j = 0;j < 70;j++){
          outfile << "+";
          this->histAry[i]--;
         	}

          outfile << std::endl;

          } else {
           outfile << i << " (  " << this->histAry[i] << "  ):";
           for(int j = 0;j < this->histAry[i];){
             outfile << "+";
             this->histAry[i]--;
           }
             outfile << std::endl;
         }

       }
  }

}

int Concavity::deepestConcavity(){
 	int max = 0;
 	int first = x1;
 	int second = x2;
  int x = first;
	int thr = first;


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


	fileHist.close();
  filePoints.close();
	outFile.close();
}
