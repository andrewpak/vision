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

		System.out.println(this.numImgRows + " " + this.numImgCols + " " + this.imgMin + " " + this.imgMax);

		this.zeroFramedAry = new int[this.numImgRows + 2][this.numImgCols + 2];
		this.zero2DAry(this.zeroFramedAry, this.numImgRows + 2, this.numImgCols + 2);	
		for(int i = 0;i < this.numImgRows + 2;i++){
			for(int j = 0;j < this.numImgCols + 2;j++){
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
		for(int i = 0;i < this.numImgRows + 2;i++){
			for(int j = 0;j < this.numImgCols + 2;j++){
				System.out.print(this.zeroFramedAry[i][j] + " ");
			}
			System.out.println();
		}

	}

	public int getRowOrigin(){
		return this.rowOrigin;
	}

	public int getColOrigin(){
		return this.colOrigin;
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
			FileWriter dialateOutFile = new FileWriter(args[2]);
			FileWriter erodeOutFile = new FileWriter(args[3]);
			FileWriter openingOutFile = new FileWriter(args[4]);
			FileWriter closingOutFile = new FileWriter(args[5]);
			FileWriter prettyPrintFile = new FileWriter(args[6]);
			
			Morphology myMorph = new Morphology(inFile, structFile);
			myMorph.loadImg(myMorph.getRowOrigin(), myMorph.getColOrigin(), inFile);
			
			dialateOutFile.close();
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
