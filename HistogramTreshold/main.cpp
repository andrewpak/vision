#include <iostream>
#include <fstream>
#include <string>

int *histAry;
int numRows, numCols, minVal, maxVal;
int thrVal;

void computeHist(std::ifstream &file){
	int i = 0;
	int j = 0;

	while(i < numRows){
		while(j < numCols){
			int val;
			file >> val;
			histAry[val]++;
			j++;
		}
		j=0;
		i++;
	}
}

void threshold(std::ifstream &file, std::ofstream &outFile3, std::ofstream &outFile4, int thrVal){
	
	file >> numRows >> numCols >> minVal >> maxVal;
	minVal = 0;
	maxVal = 1;
		
	outFile3 << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
	outFile4 << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
	
	for(int i = 0;i < numRows;++i){
		for(int j = 0;j < numCols;++j){
			int pixelVal;
			file >> pixelVal;
			if(pixelVal >= thrVal){
				outFile3 << 1 << " ";
			 	outFile4 << 1 << " ";
			} else {
				outFile3 << 0 << " ";
				outFile4 << "." << " ";
			}
		}
		outFile3 << std::endl;
		outFile4 << std::endl;
	}

}

void printHist(std::ifstream &file, std::ofstream &outfile, int *array) {
	
	outfile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;

	for(int i = 0;i < maxVal + 1;i++){
		outfile << i << " " << array[i] << std::endl;
	}

}

void dispHist(int *array, std::ofstream &outfile){
	
	outfile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
	
	for(int i = 0;i < maxVal; i++){			
			if (array[i] == 0) outfile << i << " (  " << 0 << "  ):" << std::endl; 
			while(array[i] > 0){

				if(array[i] > 70){
					int tmp = 1;

					outfile << i << " (  " << 70 << " ):";
					for(int j = 0;j < 70;j++){
									outfile << tmp << " +";
					tmp++;
					array[i]--;
				}	
				tmp = 0;
				outfile << std::endl;

				} else {
					outfile << i << " (  " << array[i] << "  ):";
					for(int j = 0;j < array[i];){
						outfile << "+";
						array[i]--;
					}
						outfile << std::endl;
				}
			
			}

	}

}

int main(int argc, char *argv[]){
	
	std::string fileName = argv[1];	
	std::ifstream inFile(fileName);
	thrVal = std::atoi(argv[2]);
	std::cout << "This is threshVal: " << thrVal << std::endl;
	std::ofstream outFile1;
	outFile1.open(argv[3]);
	std::ofstream outFile2;
	outFile2.open(argv[4]);
	std::ofstream outFile3;
	outFile3.open(argv[5]);
	std::ofstream outFile4;
	outFile4.open(argv[6]);
	 
	inFile >> numRows >> numCols >> minVal >> maxVal;
		
	std::cout << "this is numRows: " << numRows << std::endl;
	std::cout << "this is numCols: " << numCols << std::endl;
	std::cout << "this is minVal: " << minVal << std::endl;
	std::cout << "this is maxVal: " << maxVal << std::endl;
  
	histAry	= new int[maxVal + 1];
	for(int i = 0;i < maxVal + 1;i++){
		histAry[i] = 0;
	}

	for(int i = 0;i < maxVal + 1;i++){
		std::cout << histAry[i] << " ";
	}

	
	std::cout << std::endl;
	
	computeHist(inFile);	

	std::cout << "This is the histAry: " << std::endl;
	
	for(int i = 0;i <= maxVal;i++){
		std::cout << histAry[i] << " ";
	}
	
	printHist(inFile, outFile1, histAry);
	dispHist(histAry, outFile2);

	inFile.close();
	inFile.open(fileName);
	outFile3 << "The threshold value used is " << thrVal << std::endl;		
	outFile4 << "The threshold value used is " << thrVal << std::endl;
	threshold(inFile, outFile3, outFile4, thrVal);

	// collect some trash, close files

	if(histAry != NULL){
		delete [] histAry;
	}

	inFile.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();
	outFile4.close();

	return 0;
}
