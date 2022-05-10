#include <iostream>
#include <fstream>



struct Property {
    int label, numPixels, minR, minC, maxR, maxC;

};

class imageProcessing {

    private:
        int numRows, numCols, minVal, maxVal;
        int newMin, newMax, newLabel;
        int Connectness;
        int **zeroFramedAry;
        int *nonZeroNeighborAry;
        int *eqAry;

    public:
        imageProcessing(std::ifstream &inFile);
        int getNumRows();
        int getNumCols();
        int getMinVal();
        int getMaxVal();
        int** getZeroFramedAry();
        int* getEqAry();
        void loadImg(std::ifstream &inFile, int** ary);
        void imgReformat(int** ary, std::ofstream &outFile);
        void connect4Pass1();
        void connect4Pass2();
        void connect8Pass1();
        void connect8Pass2();
        void connectPass3(Property *p);
        void printCCProperty(Property *p, std::ofstream &outFile, int totalCC);
        void drawBoxes(int **ary, Property *p, int realCC);
        void updateEQ(int location, int label);
        int manageEQAry();
        void setNumRows(int n);
        void setNumCols(int n);
        void setMinVal(int n);
        void setMaxVal(int n);
        void print2DAry(int** ary, int rows, int cols);
        void setNewLabel(int n);
        int getNewLabel();
        void deleteArys();
        void setConnnectness(int n);
        int getConnnectness();


};

imageProcessing::imageProcessing(std::ifstream &inFile){
    std::cout << "Hello imageProcessing" << std::endl;

    inFile >> numRows >> numCols >> minVal >> maxVal;

    std::cout << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;

    // allocate zeroFramed
    zeroFramedAry = new int*[numRows + 2];

    for(int i = 0;i < numRows + 2;i++){
        zeroFramedAry[i] = new int[numCols + 2];
    }

    // allocate nonZero neighbor ary
    nonZeroNeighborAry = new int [5];

    // allocate eqary
    eqAry = new int[(numRows * numCols) / 4];
    //print ary test
    for(int i = 0;i < (numRows * numCols) / 4;i++){
        eqAry[i] = i;
    }

}


void imageProcessing::loadImg(std::ifstream &inFile, int** ary){
    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            inFile >> ary[i][j];
        }
    }
}

void imageProcessing::imgReformat(int** ary, std::ofstream &outFile){
    outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
    for(int i = 0;i < numRows + 1;i++){
        for(int j = 0;j < numCols + 1;j++){
            if(ary[i][j] > 9 && ary[i][j] < 100){
                outFile << ary[i][j] << "  ";
            }
            else if(ary[i][j] > 99){
                outFile << ary[i][j] << " ";
            }

            else if(ary[i][j] == -1){
                outFile << "*   ";
            }

            else {
                outFile << ary[i][j] << "   ";
            }
        }
        outFile << std::endl;
    }

    outFile << "this is the eq ary " << std::endl;
    for(int i = 0;i <= newLabel;i++){
        outFile << i << ": " << eqAry[i] << std::endl;
    }

    outFile << std::endl;
    outFile << numRows << " " << numCols << " " << minVal << " " << maxVal << std::endl;
    for(int i = 0;i <= numRows;i++){
        for(int j = 0;j <= numCols;j++){
            if(ary[i][j] == 0){
                outFile << ".   ";
            }
            else if(ary[i][j] > 9 && ary[i][j] < 100){
                outFile << ary[i][j] << "  ";
            }
            else if(ary[i][j] > 99){
                outFile << ary[i][j] << " ";
            }
            else if(ary[i][j] == -1){
                outFile << "*   ";
            }
            else {
                outFile << ary[i][j] << "   ";
            }
        }
        outFile << std::endl;
    }


}


void imageProcessing::printCCProperty(Property *p, std::ofstream &outFile, int totalCC){
    outFile << "Connected Components Property File" << std::endl;

    outFile << numRows << " " << numCols <<  " " << minVal << " " << maxVal << std::endl;

    outFile << totalCC << std::endl;

    outFile << std::endl;

    for(int i = 0;i <= totalCC;i++){
            outFile << p[i].label << std::endl;
            outFile << p[i].numPixels << std::endl;
            outFile << p[i].minR << " " << p[i].minC << std::endl;
            outFile << p[i].maxR << " " << p[i].maxC << std::endl;
            outFile << std::endl;
    }


}

void imageProcessing::connect4Pass1(){

    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                if(zeroFramedAry[i - 1][j] == 0 && zeroFramedAry[i][j - 1] == 0){
                    newLabel++;
                    zeroFramedAry[i][j] = newLabel;
                    updateEQ(zeroFramedAry[i][j], newLabel);
                }
                else if (zeroFramedAry[i - 1][j] == zeroFramedAry[i][j - 1]){
                    zeroFramedAry[i][j] = zeroFramedAry[i - 1][j];
                    updateEQ(zeroFramedAry[i][j], zeroFramedAry[i - 1][j]);
                }
                else {
                    int temp = zeroFramedAry[i][j - 1];
                    int temp2 = zeroFramedAry[i - 1][j];
                    if(temp != 0 && temp2 != 0){
                        int tempMin = std::min(temp, temp2);
                        zeroFramedAry[i][j] = tempMin;
                        updateEQ(zeroFramedAry[i - 1][j], tempMin);
                        updateEQ(zeroFramedAry[i][j - 1], tempMin);
                        updateEQ(zeroFramedAry[i][j], tempMin);
//                        updateEQ(temp2, std::min(temp, temp2));
                    }

                    else {
                        if(temp > 0){

                            zeroFramedAry[i][j] = temp;
                           // updateEQ(zeroFramedAry[i][j], temp);
                            updateEQ(temp, temp);
                        }
                        else {
                            zeroFramedAry[i][j] = temp2;

                            updateEQ(temp2, temp2);
                            //updateEQ(zeroFramedAry[i][j], temp2);
                        }
                    }

                }

            }

        }

    }


    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                std::cout << "zero Frame arry is " << zeroFramedAry[i][j] << " eqary is " << eqAry[zeroFramedAry[i][j]] <<std::endl;
                zeroFramedAry[i][j] = eqAry[zeroFramedAry[i][j]];
            }
        }
    }

}

void imageProcessing::connect4Pass2(){

    for(int i = numRows;i >= 1;i--){
        for(int j = numCols;j >= 1;j--){

            if(zeroFramedAry[i][j + 1] == 0 && zeroFramedAry[i + 1][j] == 0){
                // do nothing
            }

            else if(zeroFramedAry[i][j + 1] == zeroFramedAry[i + 1][j] == zeroFramedAry[i][j]){
                // do nothing
            }

            else {
                int temp = zeroFramedAry[i][j + 1];
                int temp2 = zeroFramedAry[i + 1][j];
                if(temp > 0 && temp2 > 0){
                    int min = std::min(temp, temp2);
                    int minLabel = std::min(min, zeroFramedAry[i][j]);
                    updateEQ(zeroFramedAry[i][j], minLabel);
                    zeroFramedAry[i][j] = minLabel;
                }
                else if(temp > 0){
                    int minLabel = std::min(temp, zeroFramedAry[i][j]);
                    updateEQ(zeroFramedAry[i][j], minLabel);
                    zeroFramedAry[i][j] = minLabel;
                }
                else if (temp2 > 0){
                    int minLabel = std::min(temp2, zeroFramedAry[i][j]);
                    updateEQ(zeroFramedAry[i][j], minLabel);
                    zeroFramedAry[i][j] = minLabel;
                }
            }

        }
    }

    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                std::cout << "zero Frame arry is " << zeroFramedAry[i][j] << " eqary is " << eqAry[zeroFramedAry[i][j]] <<std::endl;
                zeroFramedAry[i][j] = eqAry[zeroFramedAry[i][j]];
            }
        }
    }

}

void imageProcessing::connect8Pass1(){
    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                nonZeroNeighborAry[0] = zeroFramedAry[i - 1][j - 1];
                nonZeroNeighborAry[1] = zeroFramedAry[i - 1][j];
                nonZeroNeighborAry[2] = zeroFramedAry[i - 1][j + 1];
                nonZeroNeighborAry[3] = zeroFramedAry[i][j - 1];
                int temp = 9999;

                if(nonZeroNeighborAry[0] == 0
                && nonZeroNeighborAry[1] == 0
                && nonZeroNeighborAry[2] == 0
                && nonZeroNeighborAry[3] == 0){
                    newLabel++;
                    zeroFramedAry[i][j] = newLabel;
                    updateEQ(newLabel, newLabel);
                }

                else if(nonZeroNeighborAry[0] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[1] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[2] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[3] == zeroFramedAry[i][j]){
                    // do nothing to zeroFramedAry, but update EQ table for other values
                    for(int k = 0;k < 4;k++){
                        if(nonZeroNeighborAry[k] != zeroFramedAry[i][j] && nonZeroNeighborAry[k] != 0){
                            updateEQ(nonZeroNeighborAry[k], zeroFramedAry[i][j]);
                        }
                    }


                }

                else {
                    for(int k = 0;k < 4;k++){
                        int count = 0;
                        if(nonZeroNeighborAry[k] == 0){
                            // do nothing
                        }

                        else if(nonZeroNeighborAry[k] < temp){
                            temp = nonZeroNeighborAry[k];
                        }
                    }

                    zeroFramedAry[i][j] = temp;
                    updateEQ(zeroFramedAry[i][j], temp);
                    //   zeroFramedAry[i - 1][j - 1] = zeroFramedAry[i][j];
                    // if(zeroFramedAry[i - 1][j] != 0){
                    //     zeroFramedAry[i - 1][j] = zeroFramedAry[i][j];
                    // }
                    // if(zeroFramedAry[i - 1][j + 1] != 0){
                    //     zeroFramedAry[i - 1][j + 1] = zeroFramedAry[i][j];
                    // }
                    // if(zeroFramedAry[i][j + 1] != 0){
                    //     zeroFramedAry[i][j + 1] = zeroFramedAry[i][j];
                    // }
                }
            }
        }
    }

    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                zeroFramedAry[i][j] = eqAry[zeroFramedAry[i][j]];
            }
        }
    }
}

void imageProcessing::connect8Pass2(){
    for(int i = numRows;i > 0;i--){
        for(int j = numCols;j > 0;j--){
            if(zeroFramedAry[i][j] > 0){
                nonZeroNeighborAry[0] = zeroFramedAry[i][j + 1];
                nonZeroNeighborAry[1] = zeroFramedAry[i + 1][j - 1];
                nonZeroNeighborAry[2] = zeroFramedAry[i + 1][j];
                nonZeroNeighborAry[3] = zeroFramedAry[i + 1][j + 1];
                int temp = 9999;

                if(nonZeroNeighborAry[0] == 0
                && nonZeroNeighborAry[1] == 0
                && nonZeroNeighborAry[2] == 0
                && nonZeroNeighborAry[3] == 0){
                    // do nothing p(i, j) keeps label
                }

                else if(nonZeroNeighborAry[0] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[1] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[2] == zeroFramedAry[i][j] ||
                        nonZeroNeighborAry[3] == zeroFramedAry[i][j]){
                    // do nothing p(i, j) keeps label

                }

                else {
                    int count = 0;

                    for(int k = 0;k < 4;k++){
                        if(nonZeroNeighborAry[k] == 0){
                            // do nothing
                        }

                        else if(nonZeroNeighborAry[k] < temp){
                            temp = nonZeroNeighborAry[k];
                            updateEQ(nonZeroNeighborAry[k], temp);
                            count++;
                        }
                    }

                    if(count >= 2){
                        zeroFramedAry[i][j] = temp;

                        updateEQ(zeroFramedAry[i][j], temp);
                    }
                }
            }
        }
    }

    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                zeroFramedAry[i][j] = eqAry[zeroFramedAry[i][j]];
            }
        }
    }

}

void imageProcessing::connectPass3(Property *p){
    for(int i = 1;i <= numRows;i++){
        for(int j = 1;j <= numCols;j++){
            if(zeroFramedAry[i][j] > 0){
                zeroFramedAry[i][j] = eqAry[zeroFramedAry[i][j]];


                p[zeroFramedAry[i][j]].label = zeroFramedAry[i][j];

                if(p[zeroFramedAry[i][j]].numPixels == 0){
                    p[zeroFramedAry[i][j]].minR = i;
                    p[zeroFramedAry[i][j]].minC = j;
                    p[zeroFramedAry[i][j]].maxR = i;
                    p[zeroFramedAry[i][j]].maxC = j;
                }

                if(p[zeroFramedAry[i][j]].minR > i){
                    p[zeroFramedAry[i][j]].minR = i;
                }

                if(p[zeroFramedAry[i][j]].minC > j){
                    p[zeroFramedAry[i][j]].minC = j;
                }

                if(p[zeroFramedAry[i][j]].maxR < i){
                    p[zeroFramedAry[i][j]].maxR = i;
                }

                if(p[zeroFramedAry[i][j]].maxC < j){
                    p[zeroFramedAry[i][j]].maxC = j;
                }
                p[zeroFramedAry[i][j]].numPixels++;

            }
        }
    }
}

int imageProcessing::manageEQAry(){
    int realLabel = 0;

    int index = 1;
    std::cout << "this is newLabel " << newLabel << std::endl;
    while(!(index > newLabel)){
        if(index != eqAry[index]){
            eqAry[index] = eqAry[eqAry[index]];
        }

        else {
            realLabel++;
            eqAry[index] = realLabel;
        }
        index++;
    }

    return realLabel;

}

void imageProcessing::updateEQ(int location, int label){
        eqAry[location] = label;
}


void imageProcessing::drawBoxes(int **ary, Property *p, int realCC){

    int index = 1;

    while(index <= realCC){

        int minRow = p[index].minR - 1;
        int minCol = p[index].minC - 1;
        int maxRow = p[index].maxR + 1;
        int maxCol = p[index].maxC + 1;
        int label = -1;

        for(int i = minCol;i <= maxCol;i++){
            if(ary[minRow][i] > 0){
                ary[minRow][i] = ary[minRow][i];
            }

            else{
                ary[minRow][i] = label;
            }
        }

        for(int i = minRow;i <= maxRow;i++){
            if(ary[i][minCol] > 0){

                ary[i][minCol] = ary[i][minCol];
            }

            else {
                ary[i][minCol] = label;
            }
        }

        for(int i = minCol;i <= maxCol;i++){
            if(ary[maxRow][i] > 0){
                ary[maxRow][i] = ary[maxRow][i];
            }

            else {
                ary[maxRow][i] = label;
            }
        }

        for(int i = minRow;i <= maxRow;i++){
            if(ary[i][maxCol] > 0){
                ary[i][maxCol] = ary[i][maxCol];
            }
            else {
                ary[i][maxCol] = label;
            }
        }

        index++;
    }


}

int imageProcessing::getNumRows(){
    return numRows;
}

int imageProcessing::getNumCols(){
    return numCols;
}

int imageProcessing::getMinVal(){
    return minVal;
}

int imageProcessing::getMaxVal(){
    return maxVal;
}

int** imageProcessing::getZeroFramedAry(){
    return zeroFramedAry;
}

int* imageProcessing::getEqAry(){
    return eqAry;
}

void imageProcessing::setNumRows(int n){
    numRows = n;
}

void imageProcessing::setNumCols(int n){
    numCols = n;
}

void imageProcessing::setMinVal(int n){
    minVal = n;
}

void imageProcessing::setMaxVal(int n){
    maxVal = n;
}

void imageProcessing::setNewLabel(int n){
    newLabel = n;
}

int imageProcessing::getNewLabel(){
    return newLabel;
}

void imageProcessing::setConnnectness(int n){
    Connectness = n;
}

int imageProcessing::getConnnectness(){
    return Connectness;
}

void imageProcessing::print2DAry(int **ary, int rows, int cols){
    for(int i = 0;i < rows;i++){
        for(int j = 0;j < cols;j++){
                std::cout << ary[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void imageProcessing::deleteArys(){

    for(int i = 0;i < numRows + 2;i++){
        delete [] zeroFramedAry[i];
    }

    delete [] zeroFramedAry;
    delete [] nonZeroNeighborAry;
    delete [] eqAry;
}


int main(int argc, char **argv) {

    std::cout << "Hello Connect Components" << std::endl;

    std::ifstream inFile(argv[1]);

    imageProcessing imageProcessor(inFile);

    imageProcessor.print2DAry(imageProcessor.getZeroFramedAry(), imageProcessor.getNumRows() + 2, imageProcessor.getNumCols() + 2);
    imageProcessor.setNewLabel(0);
    std::cout << "this is the newLabel " << imageProcessor.getNewLabel() << std::endl;

    imageProcessor.loadImg(inFile, imageProcessor.getZeroFramedAry());


    imageProcessor.print2DAry(imageProcessor.getZeroFramedAry(), imageProcessor.getNumRows() + 2, imageProcessor.getNumCols() + 2);

    int connectness = std::atoi(argv[2]);
    imageProcessor.setConnnectness(connectness);

    std::ofstream outFile(argv[3]);
    std::ofstream labelFile(argv[4]);
    std::ofstream outFile2(argv[5]);
    std::cout << "This is connectness " << imageProcessor.getConnnectness() << std::endl;
    int trueNumCC = 0;
    if(connectness == 4){
        imageProcessor.connect4Pass1();
        outFile << "this is after Connect4Pass1 " << std::endl;
        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);

        imageProcessor.connect4Pass2();
        outFile << "this is after Connect4Pass2 " << std::endl;
        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);

        trueNumCC = imageProcessor.manageEQAry();

        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);
    }

    else if(connectness == 8){

        imageProcessor.connect8Pass1();
        outFile << "this is after Connect8Pass1" << std::endl;
        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);

        imageProcessor.connect8Pass2();
        outFile << "this is after Connect8Pass2" << std::endl;
        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);

        trueNumCC = imageProcessor.manageEQAry();
        outFile << "this is after managing the EQ ary" << std::endl;
        imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);
    }

    else {
        std::cout << "Run the program again, next time, with the correct connectness..." << std::endl;
        std::cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@^^^^^^^^^^^^^>!" << std::endl;
        std::cout << "exiting now............." << std::endl;
        exit(0);
    }



    Property CCproperty[trueNumCC];
    std::cout << "This is numPixels in property struct " << CCproperty[0].numPixels << " this is trueNum " << trueNumCC << std::endl;
    for(int i = 0;i <= trueNumCC;i++){
        CCproperty[i].numPixels = 0;
        CCproperty[i].label = 0;
        CCproperty[i].minR = 0;
        CCproperty[i].minC = 0;
        CCproperty[i].maxR = 0;
        CCproperty[i].maxC = 0;
      }

    imageProcessor.connectPass3(CCproperty);
    imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);
    imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), labelFile);
    imageProcessor.printCCProperty(CCproperty, outFile2, trueNumCC);

    imageProcessor.drawBoxes(imageProcessor.getZeroFramedAry(), CCproperty, trueNumCC);

    imageProcessor.imgReformat(imageProcessor.getZeroFramedAry(), outFile);
    outFile << std::endl << "This is the true number CC: " << trueNumCC << std::endl;
// delete arrays and close i/o
    imageProcessor.deleteArys();

    inFile.close();
    outFile.close();
    outFile2.close();
    labelFile.close();
    return 0;

}
