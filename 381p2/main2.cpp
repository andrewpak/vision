#include <iostream>
#include <fstream>

int numRows, numCols, minVal, maxVal; 
int maskRows, maskCols, maskMin, maskMax, newMin, newMax, thrVal;

int **mirrorFramedAry;
int **medianAry;
int **GaussAry;
int **thrAry;
int *neighborAry;
int **maskAry;

// /////////////////////////////////////////////////  //

// creating a helper function to print array's and 		//
// delete array's 																		//
// not part of project spec but it makes life easier 	//
	 
// ////////////////////////////////////////////////// //

void check2dAry(int **array, int rows, int cols){
	for(int i = 0;i < rows;i++){
		for(int j = 0;j < cols;j++){
			if(array[i][j] < 10) {
				std::cout << array[i][j] << "  ";
			}	else {
				std::cout << array[i][j] << " ";
			}
		}
		std::cout << std::endl;
	}

}

void destroy1dAry(int *array){

}

void destroy2dAry(int **array){

}


/////////////////////////////////////////////////////////

void loadMask(int **ary, std::ifstream &file){
	for(int i = 0;i < maskRows;i++){
		for(int j = 0;j < maskCols;j++){
			 file >> ary[i][j];
		}
	}
}

void loadImage(int **ary, std::ifstream &file){
	for(int i = 1;i < numRows + 1;i++){
		for(int j = 1;j < numCols + 1;j++){
			file >> ary[i][j];
		}
	}		
}

void mirrorFraming(int **ary) {
	
	for(int i = 1;i < numCols + 1;i++){
			ary[0][i] = ary[1][i];
	}
	
	for(int i = 1;i < numRows + 1;i++){
		ary[i][numCols + 1] = ary[i][numCols];
	}
	
	for(int i = numCols + 1;i > 0;i--){
		ary[numRows + 1][i] = ary[numRows][i];
	}
}

int main (int argc, char **argv){

	std::cout << "Starting Morphology...." << std::endl;	
	std::string fileName1 = argv[1];
	std::string fileName2 = argv[2];
	std::cout << "Opening files...." << std::endl;
	std::ifstream inFile(fileName1), maskFile(fileName2);	
	std::ofstream outFile1, outFile2, outFile3, outFile4;

	inFile >> numRows >> numCols >> minVal >> maxVal;
	
	std::cout << "The image header is..." << std::endl;
	std::cout << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
	std::cout << "Starting read of mask file...." << std::endl;
	maskFile >> maskRows >> maskCols >> maskMin >> maskMax;
	std::cout << "The mask header is....." << std::endl;
	std::cout << maskRows << " " << maskCols <<  " " << maskMin << " " << maskMax << std::endl;

	std::cout << "Dynamically allocate arrays....<$#>.." << std::endl;

	neighborAry = new int[9];

	mirrorFramedAry = new int*[numRows + 2];
	for(int i = 0;i < numRows + 2;++i){
		mirrorFramedAry[i] = new int[numCols + 2];
	}

  maskAry = new int*[maskRows];
	for(int i = 0;i < maskRows;++i){
		maskAry[i] = new int[maskCols];
	}

	// load maskFile into maskAry
	loadMask(maskAry, maskFile);
	// ** remove this later ** //
	// checking if got the right mask //
	check2dAry(maskAry, maskRows, maskCols);

	loadImage(mirrorFramedAry, inFile);

	check2dAry(mirrorFramedAry, numRows + 2, numCols + 2);

	std::cout << std::endl;
	std::cout << "This is the mirror framed array : ~%" << std::endl;

	mirrorFraming(mirrorFramedAry);
	check2dAry(mirrorFramedAry, numRows + 2, numCols + 2);

	// Delete arrays, close files..//
	//														 //
	std::cout << "Delete arrays...." << std::endl;

	if(neighborAry != NULL){
		delete [] neighborAry;
	}
	
	if(mirrorFramedAry != NULL){
		for(int i = 0;i < numRows + 2;i++){
			delete [] mirrorFramedAry[i];
		}
		delete [] mirrorFramedAry;
	}
  
	if(maskAry != NULL){
		for(int i = 0;i < maskRows;i++){
			delete [] maskAry[i];
		}
		delete [] maskAry;
	}


	std::cout <<  "Close all i / o files..." << std::endl;
	inFile.close();
	maskFile.close();
	outFile1.close();
	outFile2.close();
	outFile3.close();
	outFile4.close();

}
