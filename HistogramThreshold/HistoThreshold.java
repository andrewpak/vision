import java.util.*;
import java.io.*;

public class HistoThreshold {
    private static int numRows, numColumns, minVal, maxVal, thresholdValue;
    private static int[] histAry;
    
    // Computes a Histogram of the pixel intensity values of provided image
    public static void computeHist(String fileName){
        try{
        Scanner inFile1 = new Scanner(new FileReader(fileName));
        String header = inFile1.nextLine();
        // ** Step 1: get maxVal, numRows, numColumns, minVal ** //
        maxVal = Integer.parseInt(header.substring(9,11)); 
        numRows = Integer.parseInt(header.substring(1,3));
        numColumns = Integer.parseInt(header.substring(4,6));
        minVal = Integer.parseInt(header.substring(7,8));
        // ** Step 2: dynamically allocate histAry ** //
        histAry = new int[maxVal + 1];
        while(inFile1.hasNext()){
            histAry[inFile1.nextInt()]++;
        }
        inFile1.close();
        System.out.println("Sucessfully computed histAry");
        } catch (IOException e) {

        }
       
    }

    // ~Prints the Header and Pairs <i, j> in outFile1~ //
    public static void printHist(String fileName){
        try {
            FileWriter outPut1Writer = new FileWriter(fileName);
            outPut1Writer.write(numRows + " " + numColumns + " " + minVal + " " + maxVal + "\n");
            for(int i = 0;i < histAry.length;i++){
                outPut1Writer.write(i + " " + histAry[i]+ "\n");
            }
            outPut1Writer.close();
            System.out.println("Successfully wrote outPut1");
        } catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
        
    }

    // ~Prints the "Pretty output" of the Histogram~ // 
    public static void dispHist(String fileName){
            try {
                FileWriter outPut2Writer = new FileWriter(fileName);
                outPut2Writer.write(numRows + " " + numColumns + " " + minVal + " " + maxVal + "\n");
                
                for(int i = 0;i < histAry.length;i++){
                    String intensity = "";
                    for(int j = 0; j < histAry[i];j++){
                        intensity = intensity + "+";
                    }
                    outPut2Writer.write(i + " (" + histAry[i] + "):" + intensity + "\n");
                }
                outPut2Writer.close();
                System.out.println("Successfully wrote outFile2");
            } catch (IOException e){
                System.out.println("An error occurred");
                e.printStackTrace();
            }
    }
    // ~Performs threshold on the image, writes outFile3.txt which is the 
    // nxn binary matrix, also writes outFile4.txt which is the same matrix with '.' replacing
    // all zeros, for the sake of clearer visualization of the image thresholding~ //
    public static void threshold(String inFile, FileWriter outPut3Writer, FileWriter outPut4Writer, int thrVal){
        
        minVal = 0;
        maxVal = 1;
       
            try {
                Scanner inFile2 = new Scanner (new FileReader(inFile));
                inFile2.nextLine();
                outPut3Writer.write(numRows + " " + numColumns + " " + minVal + " " + maxVal + "\n");
                outPut4Writer.write(numRows + " " + numColumns + " " + minVal + " " + maxVal + "\n");
                
                while(inFile2.hasNext()){
                    int pixelVal = 0;
                    for (int i = 0; i < numColumns; i++) {
                        if(inFile2.hasNext()){
                            pixelVal = inFile2.nextInt();
                        }
                        
                        if (pixelVal >= thrVal) {
                            outPut3Writer.write(maxVal + " ");
                            outPut4Writer.write(maxVal + " ");
        
                        } else {
                            outPut3Writer.write(minVal + " ");
                            outPut4Writer.write("." + " ");
        
                        }
        
                    }
                    outPut3Writer.write("\n");
                    outPut4Writer.write("\n");
                }
                outPut3Writer.close();
                System.out.println("Successfully wrote outFile3");
                outPut4Writer.close();
                System.out.println("Successfully wrote outFile4");
                inFile2.close();
                System.out.println("closed Scanner inFile2");
                } catch (IOException e){
                    System.out.println("Error occurred");
                }
        } 
        
            
    // ** DRIVER CODE ** //
    public static void main(String[] args) {

        try {

            // **  Step 0: open input file use args[0], threshold value args[1] ** //
            String inFile = new String(args[0]);
            
            thresholdValue = Integer.parseInt(args[1]);
            String outFile1 = new String(args[2]);
            String outFile2 = new String(args[3]);
            String outFile3String = new String(args[4]);
            String outFile4String = new String(args[5]);
            FileWriter outFile3 = new FileWriter(outFile3String);
            FileWriter outFile4 = new FileWriter(outFile4String);

            /////////////////////////////////////////////////////////////////////
            //                                                                 //     
            // This was here as per the spec sheet, but in the lecture notes 2 //
            // it says this is a part of computeHist, so it is now there...    // 
            // Step 1: numRows, numCols, minVal, maxVal <- read from inFile    // 
            // maxVal = Integer.parseInt(header.substring(9,11));              // 
            // numRows = Integer.parseInt(header.substring(1,3));              // 
            // numColumns = Integer.parseInt(header.substring(4,6));           // 
            // minVal = Integer.parseInt(header.substring(7,8));               // 
            //                                                                 // 
            /////////////////////////////////////////////////////////////////////

            
            // ** Step 1, 2, 3: Compute Histogram Array ** //
            computeHist(inFile);

            // ** Step 4: printHist(outFile1) ** //
            printHist(outFile1);

            // ** Step 5: dispHist(outFile2) ** //
            dispHist(outFile2);

            // ** Step 6: close inFile, reopen inFile ** //
            // **  Scanner closes within each method upon finishing  ** //

            // **Step 7** //
            outFile3.write("The threshold value uses is " + thresholdValue + "\n");
            outFile4.write("The threshold value uses is " + thresholdValue + "\n");
    
            // ** Step 8: threshold(inFile, outFile3, outFile4, thrVal) ** //
            threshold(inFile, outFile3, outFile4, thresholdValue);
            
            // ~ALL SCANNERS CLOSED, FINISHED~ //
            
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        
    }

}