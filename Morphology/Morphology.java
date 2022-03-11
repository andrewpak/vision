import java.util.*;
import java.io.*;


class Morphology {


	private static int numImgRows, numImgCols, imgMin, imgMax;
	private static int numStructRows, numStructCols, structMin, structMax;
	private static int rowOrigin, colOrigin;
	private static int rowFrameSize, colFrameSize;
	private static int extraRows, extraCols;
	private static int rowSize, colSize;

	private static int zeroFramedAry[][];
	private static int morphAry[][];

	private static int tempAry[][];
	private static int structAry[][];

	public Morphology(Scanner inFile, Scanner structFile){
		
		this.numImgRows = inFile.nextInt();
		this.numImgCols = inFile.nextInt();
		this.imgMin = inFile.nextInt();
		this.imgMax = inFile.nextInt();
		this.numStructRows = structFile.nextInt();
		this.numStructCols = structFile.nextInt();
		this.structMin = structFile.nextInt();
		this.structMax = structFile.nextInt();
		this.rowOrigin = structFile.nextInt();
		this.colOrigin = structFile.nextInt();
		rowFrameSize = this.numStructRows / 2;
		colFrameSize = this.numStructCols / 2;
		extraRows = rowFrameSize * 2;
		extraCols = colFrameSize * 2;
		rowSize = numImgRows + extraRows;
		colSize = numImgCols + extraCols;
		System.out.println("this is rowFrameSize and Col Frame Size " + rowFrameSize + " " + colFrameSize);
		System.out.println(this.numImgRows + " " + this.numImgCols + " " + this.imgMin + " " + this.imgMax);

		this.zeroFramedAry = new int[rowSize][colSize];
		this.zero2DAry(this.zeroFramedAry, rowSize, colSize);	
		this.structAry = new int [this.numStructRows][this.numStructCols];
		this.morphAry = new int [rowSize][colSize];
		this.tempAry = new int [rowSize][colSize];
		
		for(int i = 0;i < rowSize;i++){
			for(int j = 0;j < colSize;j++){
				System.out.print(zeroFramedAry[i][j] + " ");
			}
			System.out.println();
		}
		System.out.println();
	
	}
	
	public void zero2DAry(int ary[][], int nRows, int nCols){
		for(int i = 0;i < nRows;i++){
			for(int j = 0;j < nCols;j++){
				ary[i][j] = 0;
			}
		}
	}
	
	public void loadImg(int rowOrigin, int colOrigin, Scanner inFile){
		for(int i = rowOrigin;i <= this.numImgRows;i++){
			for(int j = colOrigin;j <= this.numImgCols;j++){
				if(inFile.hasNext()){
				this.zeroFramedAry[i][j] = inFile.nextInt();
				}
			}
		}
		System.out.println("numImgRows is " + this.numImgRows);
		System.out.println("numImgCols is " + this.numImgCols);
		for(int i = 0;i < rowSize;i++){
			for(int j = 0;j < colSize;j++){
				System.out.print(this.zeroFramedAry[i][j] + " ");
			}
			System.out.println();
		}

	}

	public void prettyPrint(int[][] array, FileWriter prettyPrintFile){
		try {
		prettyPrintFile.write(numImgRows + " " + numImgCols + " " + imgMin + " " + imgMax);
		prettyPrintFile.write('\n');
		for(int i = rowFrameSize;i < rowSize;i++){
			for(int j = colFrameSize;j < colSize;j++){
				if(array[i][j] == 0){
					prettyPrintFile.write(". ");
				}
				else {
					prettyPrintFile.write("1 ");
				}
			}
			prettyPrintFile.write('\n');
		}
		} catch (IOException e) {
			System.out.println("Error");
			e.printStackTrace();
		}
	}

	public void loadStruct(Scanner struct, int[][] structAry){
		for(int i = 0;i < this.numStructRows;i++){
			for(int j = 0;j < this.numStructCols;j++){
				structAry[i][j] = struct.nextInt();
			}
		}	
		
		System.out.println();

		for(int i = 0;i < this.numStructRows;i++){
			for(int j = 0;j < this.numStructCols;j++){
				System.out.print(structAry[i][j] + " ");
			}
			System.out.println();
		}
	}

	public void computeDilation(int[][] inAry, int[][] outAry){
		//System.out.println("rowframesize and column frame size are: " + rowFrameSize + " " + colFrameSize );
		for(int i = rowFrameSize;i < rowSize;i++){
			for(int j = colFrameSize;j < colSize;j++){
				if(inAry[i][j] > 0){
					this.onePixelDilation(i, j, outAry); // removed inAry
				}
			}
		}
	}

	public void onePixelDilation(int i,int j, int[][] outAry){
		int tempI = i - rowOrigin;
		int tempJ = j - colOrigin;
		for(int k = 0;k < numStructRows;k++){
			for(int z = 0;z < numStructCols;z++){
				if(structAry[k][z] > 0){
					outAry[tempI][tempJ] = 1;
				}
				tempJ++;
			}
			tempJ -= numStructCols;
			tempI++;
		}	
	}

	public void computeErosion(int[][] inAry, int[][] outAry){
		for(int i = rowFrameSize;i < rowSize;i++){
			for(int j = colFrameSize;j < colSize;j++){
				if(inAry[i][j] > 0){
					onePixelErosion(i, j, inAry, outAry);
				}
			}
		}	
	}
	
	public void onePixelErosion(int i, int j, int[][] inAry, int[][] outAry){
	 int iOffSet = i - rowOrigin;
	 int jOffSet = j - colOrigin;
	 boolean matchFlag = true;

	 int rIndex = 0;
	 while(matchFlag == true && rIndex < numStructRows){
	 int cIndex = 0;
	 while(matchFlag == true && cIndex < numStructCols){
	 if(structAry[rIndex][cIndex] > 0 && inAry[iOffSet + rIndex][jOffSet + cIndex] <= 0){
		 matchFlag = false;
	 } 
	 cIndex++;
	 }
	 rIndex++;
	 }

	 if(matchFlag == true){
		 outAry[i][j] = 1;
	 }
	 else {
		 outAry[i][j] = 0;
	 }

	}
	
	public void computeClosing(int[][] zeroFramedAry, int[][] morphAry, int[][] tempAry){
		computeDilation(zeroFramedAry, tempAry);
		computeErosion(tempAry, morphAry);
	
	}

	public void computeOpening(int[][] zeroFramedAry, int[][] morphAry, int[][] tempAry){
		computeErosion(zeroFramedAry, tempAry);
		computeDilation(tempAry, morphAry);
	}
	
	public void aryToFile(int[][] array, FileWriter outFile){
		try {
			outFile.write(numImgRows + " " + numImgCols + " " + imgMin + " " + imgMax);
			outFile.write('\n');
			for(int i = rowFrameSize;i < rowSize;i++){
				for(int j = colFrameSize;j < colSize;j++){
					
					outFile.write(array[i][j] + " ");
			}
			outFile.write('\n');
		}
		outFile.write('\n');
		}
		catch (IOException e){
			System.out.println("An error occured yo!");
			e.printStackTrace();
		}
	}

	public int getRowOrigin(){
		return this.rowOrigin;
	}

	public int getColOrigin(){
		return this.colOrigin;
	}

	public int[][] getZeroFramedAry(){
		return this.zeroFramedAry;
	}

	public int[][] getStructAry(){
		return this.structAry;
	}
	
	public int[][] getMorphAry(){
		return this.morphAry;
	}
	
	public int[][] getTempAry(){
		return this.tempAry;
	}

	public int getNumStructRows(){
		return this.numStructRows;
	}
	
	public int getNumStructCols(){
		return this.numStructCols;
	}
	
	public int getImgRows(){
		return this.numImgRows;
	}

	public int getImgCols(){
		return this.numImgCols;
	}
	
	public int getRowSize(){
		return this.rowSize;
	}
	
	public int getColSize(){
		return this.colSize;
	}

	public static void main(String args[]){
		System.out.println("hello world");

		if(args.length < 7){
			System.out.println("Expecting 7 arguments, exiting now...");
			System.exit(1);
		}
		
		try {
			Scanner inFile = new Scanner(new FileReader(args[0]));
			Scanner structFile = new Scanner(new FileReader(args[1]));	
			FileWriter dilateOutFile = new FileWriter(args[2]);
			FileWriter erodeOutFile = new FileWriter(args[3]);
			FileWriter openingOutFile = new FileWriter(args[4]);
			FileWriter closingOutFile = new FileWriter(args[5]);
			FileWriter prettyPrintFile = new FileWriter(args[6]);
			
			Morphology myMorph = new Morphology(inFile, structFile);
			myMorph.loadImg(myMorph.getRowOrigin(), myMorph.getColOrigin(), inFile);
			prettyPrintFile.write("This is the zeroFramedAry \n");
			myMorph.prettyPrint(myMorph.getZeroFramedAry(), prettyPrintFile);	
			
			myMorph.zero2DAry(myMorph.getStructAry(), myMorph.getNumStructRows(), myMorph.getNumStructCols());	
			myMorph.loadStruct(structFile, myMorph.getStructAry());

			myMorph.zero2DAry(myMorph.getMorphAry(), myMorph.getRowSize(), myMorph.getColSize());
			myMorph.computeDilation(myMorph.getZeroFramedAry(), myMorph.getMorphAry());
			myMorph.aryToFile(myMorph.getMorphAry(), dilateOutFile);
			prettyPrintFile.write("This is the morphAry after computeDilation \n");
			myMorph.prettyPrint(myMorph.getMorphAry(), prettyPrintFile);
			
			
			myMorph.zero2DAry(myMorph.getMorphAry(), myMorph.getRowSize(), myMorph.getColSize());
			myMorph.computeErosion(myMorph.getZeroFramedAry(), myMorph.getMorphAry());
			myMorph.aryToFile(myMorph.getMorphAry(), erodeOutFile);
			prettyPrintFile.write("This is the morphAry after computeErosion \n");
			myMorph.prettyPrint(myMorph.getMorphAry(), prettyPrintFile);

			myMorph.zero2DAry(myMorph.getMorphAry(), myMorph.getRowSize(), myMorph.getColSize());
			myMorph.computeOpening(myMorph.getZeroFramedAry(), myMorph.getMorphAry(), myMorph.getTempAry());
			myMorph.aryToFile(myMorph.getMorphAry(), openingOutFile);
			prettyPrintFile.write("This is the morphAry after computeOpening \n");
			myMorph.prettyPrint(myMorph.getMorphAry(), prettyPrintFile);
			

			myMorph.zero2DAry(myMorph.getMorphAry(), myMorph.getRowSize(), myMorph.getColSize());
			myMorph.computeClosing(myMorph.getZeroFramedAry(), myMorph.getMorphAry(), myMorph.getTempAry());
			myMorph.aryToFile(myMorph.getMorphAry(), closingOutFile);
			prettyPrintFile.write("This is the morphAry after computeClosing \n");
			myMorph.prettyPrint(myMorph.getMorphAry(), prettyPrintFile);

			dilateOutFile.close();
			erodeOutFile.close();
			openingOutFile.close();
			closingOutFile.close();
			prettyPrintFile.close();

			}catch(IOException e){	
				System.out.println("error");
				e.printStackTrace();
			}
	}

}
