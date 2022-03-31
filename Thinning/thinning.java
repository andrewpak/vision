import java.util.*;
import java.io.*;


class imageProcessing {



    private int numRows, numCols, minVal, maxVal;

    private  int changeFlag;

    private int cycleCount;

    private int [][] aryOne;
    private int [][] aryTwo;


    public imageProcessing(Scanner inFile){

        numRows = inFile.nextInt();
        numCols = inFile.nextInt();
        minVal = inFile.nextInt();
        maxVal = inFile.nextInt();

        System.out.println(numRows + " " + numCols + " " + minVal + " " + maxVal);

    }

    public void zeroFrame(){
        aryOne = new int[numRows + 2][numCols + 2];
        aryTwo = new int[numRows + 2][numCols + 2];
        for(int i = 0;i < numRows + 2;i++){
            for(int j = 0;j < numCols + 2;j++){
                aryOne[i][j] = 0;
                aryTwo[i][j] = 0;
            }
        }
    }
    public void loadImg(Scanner inFile, int [][]aryOne){
        for(int i = 1;i <= numRows;i++){
            for(int j = 1;j <= numCols;j++){
                if(inFile.hasNext()) aryOne[i][j] = inFile.nextInt();
            }
        }
    }

    public void prettyPrint(int [][] array, FileWriter outFile, int cycleCount){
        try{
            outFile.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
            outFile.write("Cycle Count: " + cycleCount + "\n");
            for(int i = 0;i < numRows + 2;i++){
                for(int j = 0;j < numCols + 2;j++){
                    if(array[i][j] == 0){
                        outFile.write(". ");
                    }
                    else {
                        outFile.write(array[i][j] + " ");
                    }
                }
                outFile.write('\n');
            }
        } catch(IOException e){
            System.out.println("Error writing file");
            e.printStackTrace();
        }
    }


    public void copyArys(int [][] aryOne, int[][] aryTwo){
        for(int i = 0;i < numRows + 2;i++){
            for(int j = 0;j < numCols + 2;j++){
                aryOne[i][j] = aryTwo[i][j];
            }
        }
    }

    public void thinning(int [][] aryOne, int [][] aryTwo){
        northThinning(aryOne, aryTwo);
        copyArys(aryOne, aryTwo);
        southThinning(aryOne, aryTwo);
        copyArys(aryOne, aryTwo);
        westThinning(aryOne, aryTwo);
        copyArys(aryOne, aryTwo);
        eastThinning(aryOne, aryTwo);
        copyArys(aryOne, aryTwo);
    }
    // helper method for checking condition 2
    public Boolean checkFourNeighbors(int [][] ary, int row, int col){
        int tempRow = row - 1;
        int tempCol = col - 1;
        int countNeighbors = 0;
        for(int i = tempRow;i < tempRow + 3;i++){
            for(int j = tempCol;j < tempCol + 3;j++){
                if(i == row && j == col){
                    continue;
                }
                if(ary[i][j] > 0){
                    countNeighbors++;
                }
            }
        }
        if(countNeighbors >= 4){
            return true;
        } else {
            return false;
        }
    }

    public Boolean checkThreeNeighbors(int [][] ary, int row, int col){
        int tempRow = row - 1;
        int tempCol = col - 1;
        int countNeighbors = 0;
        for(int i = tempRow;i < tempRow + 3;i++){
            for(int j = tempCol;j < tempCol + 3;j++){
                if(i == row && j == col){
                    continue;
                }
                if(ary[i][j] > 0){
                    countNeighbors++;
                }
            }
        }
        if(countNeighbors >= 3){
            return true;
        } else {
            return false;
        }
    }

    public Boolean checkConnected(int [][] ary, int row, int col){
        // case 1
        //
        if(ary[row - 1][col - 1] == 1 && ary[row - 1][col] == 0 && ary[row][col - 1] == 0){
            return true;
        }
        // case 2
        if(ary[row - 1][col + 1] == 1 && ary[row - 1][col] == 0 && ary[row][col + 1] == 0){
            return true;
        }
        // case 3
        if(ary[row + 1][col - 1] == 1 && ary[row][col - 1] == 0 && ary[row + 1][col] == 0){
            return true;
        }
        // case 4
        if(ary[row + 1][col + 1] == 1 && ary[row][col + 1] == 0 && ary[row + 1][col] == 0) {
            return true;
        }
        // case 5
        if(ary[row][col - 1] == 0 && ary[row][col + 1] == 0){
               return true;
        }
        //// case 6
        if(ary[row - 1][col] == 0 && ary[row + 1][col] == 0){
              return true;
        }
        return false;
    }

    public void northThinning(int [][] aryOne, int [][] aryTwo){
        int change = 0;
        for(int i = 1;i <= numRows;i++){
            for(int j = 1;j <= numCols;j++){
                if(aryOne[i][j] > 0){
                    if(aryOne[i - 1][j] == 0 && checkFourNeighbors(aryOne, i, j) && checkConnected(aryOne, i, j) != true){
                        aryTwo[i][j] = 0;
                        change++;
                    }
                    else {
                        aryTwo[i][j] = aryOne[i][j];
                    }
                }
            }
        }
        if(change > 0){
            setChangeFlag(1);
        }
        else {
            setChangeFlag(0);
        }
    }

    public void southThinning(int [][] aryOne, int [][] aryTwo){
        int change = 0;
        for(int i = 1;i <= numRows;i++){
            for(int j = 1;j <= numCols;j++){
                if(aryOne[i][j] > 0){
                    if(aryOne[i + 1][j] == 0 && checkFourNeighbors(aryOne, i, j) == true && checkConnected(aryOne, i, j) != true){
                        aryTwo[i][j] = 0;
                        change++;
                    }
                    else {
                        aryTwo[i][j] = aryOne[i][j];
                    }
                }
            }
        }
        if(change > 0){
            setChangeFlag(1);
        }
        else {
            setChangeFlag(0);
        }
    }

    public void westThinning(int [][] aryOne, int [][] aryTwo){
        int change = 0;
        for(int i = 1;i <= numRows;i++){
            for(int j = 1;j <= numCols;j++){
                if(aryOne[i][j] > 0){
                    if(aryOne[i][j - 1] == 0 && checkThreeNeighbors(aryOne, i, j) && checkConnected(aryOne, i, j) != true){
                        aryTwo[i][j] = 0;
                        change++;
                    }
                    else {
                        aryTwo[i][j] = aryOne[i][j];
                    }
                }
            }
        }
        if(change > 0){
            setChangeFlag(1);
        }
        else {
            setChangeFlag(0);
        }
    }

    public void eastThinning(int [][] aryOne, int [][] aryTwo){
        int change = 0;
        for(int i = 1;i <= numRows;i++){
            for(int j = 1;j <= numCols;j++){
                if(aryOne[i][j] > 0){
                    if(aryOne[i][j + 1] == 0 && checkThreeNeighbors(aryOne, i, j) && checkConnected(aryOne, i, j) != true){
                        aryTwo[i][j] = 0;
                        change++;
                    }
                    else {
                        aryTwo[i][j] = aryOne[i][j];
                    }
                }
            }
        }
        if(change > 0){
            setChangeFlag(1);
        }
        else{
            setChangeFlag(0);
        }
    }

    public void printAry(int [][] ary, FileWriter outFile){
        try{
            outFile.write(numRows + " " + numCols + " " + minVal + " " + maxVal + "\n");
            for(int i = 1;i <= numRows;i++){
                for(int j = 1;j <= numCols;j++){
                    outFile.write(ary[i][j] + " ");
                }
                outFile.write("\n");
            }
        } catch (IOException e){
            System.out.println("Error writing..");
            e.printStackTrace();
        }

    }
    // function for debugging //
    public void consolePrintAry(int [][] array){
        for(int i = 0;i < numRows + 2;i++){
            for(int j = 0;j < numCols + 2;j++){
                System.out.print(array[i][j] + " ");
            }
            System.out.println();
        }
    }

    public int [][] getAryOne(){
        return aryOne;
    }

    public int [][] getAryTwo(){
        return aryTwo;
    }

    public int getCycleCount(){
        return cycleCount;
    }

    public void setCycleCount(int n){
        cycleCount = n;
    }

    public void incCycleCount(){
        cycleCount++;
    }

    public void setChangeFlag(int n){
        changeFlag = n;
    }

    public int getChangeFlag(){
        return changeFlag;
    }



    public static void main(String args[]){
       System.out.println("Hello Thinning");
       if(args.length < 3){
           System.out.println("Expecting 3 arguments..");
           System.exit(0);
       }
       try{
           Scanner inFile = new Scanner(new FileReader(args[0]));
           FileWriter outFile1 = new FileWriter(args[1]);
           FileWriter outFile2 = new FileWriter(args[2]);
           imageProcessing imgProcessor = new imageProcessing(inFile);

           imgProcessor.zeroFrame();
           imgProcessor.loadImg(inFile, imgProcessor.getAryOne());
           imgProcessor.consolePrintAry(imgProcessor.getAryOne());
           imgProcessor.setCycleCount(0);
           imgProcessor.prettyPrint(imgProcessor.getAryTwo(), outFile2, 0);
           imgProcessor.setChangeFlag(0);

           do {
               imgProcessor.thinning(imgProcessor.getAryOne(), imgProcessor.getAryTwo());
               imgProcessor.incCycleCount();
               imgProcessor.prettyPrint(imgProcessor.getAryTwo(), outFile2, imgProcessor.getCycleCount());

           }
           while (imgProcessor.getChangeFlag() > 0);
           imgProcessor.printAry(imgProcessor.getAryOne(), outFile1);
           inFile.close();
           outFile1.close();
           outFile2.close();

       } catch (IOException e) {
           System.out.println("error");
           e.printStackTrace();
       }
    }
}
