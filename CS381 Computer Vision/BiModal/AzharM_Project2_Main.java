import java.io.*;
import java.util.Arrays;
import java.util.Scanner;



public class AzharM_Project2_Main {
    public static class BiMeans{
        int numRows, numCols, minVal, maxVal;
        int BiGaussThrVal;
        int histHeight;
        int maxHeight;
        int[] histAry;
        int[] GaussAry;
        int[] bestFitGaussAry;
        char[][] GaussGraph;
        char[][] gapGraph;

        public BiMeans(int numRows, int numCols, int minVal, int maxVal, FileWriter logFile) throws IOException {
            logFile.write("Creating Object\n");
            this.numRows = numRows;
            this.numCols = numCols;
            this.minVal = minVal;
            this.maxVal = maxVal;
            maxHeight = 0;
            histAry = new int[maxVal + 1];
            GaussAry = new int[maxVal + 1];
            bestFitGaussAry = new int[maxVal + 1];
            setZero(histAry, logFile);
            setZero(GaussAry,logFile);
            setZero(bestFitGaussAry,logFile);
        }

        public int loadHist(Scanner inFile, FileWriter logFile) throws IOException {
            logFile.write("Entering loadHist\n");
            int max = -1;
            for(int i = 0; i <= maxVal; i++){
                inFile.nextInt();
                histAry[i] = inFile.nextInt();
                if(histAry[i] > max){
                    max = histAry[i];
                }
            }
            logFile.write("Exiting loadHist\n");
            return max;
        }
        public void printHist(FileWriter logFile, FileWriter histFile) throws IOException {
            logFile.write("Entering printHist\n");
            for (int i = 0; i <= maxVal; i++){
                histFile.write(i +" "+ histAry[i] + "\n");
            }
            logFile.write("Exiting printHist\n");
        }
        public void dispHist(FileWriter logFile, FileWriter histFile) throws IOException {
            logFile.write("Entering dispHist\n");
            for(int i = 0; i <= maxVal; i++){
                histFile.write(i +" ("+ histAry[i] + "): ");
                for(int j = 0; j < histAry[i]; j++){
                    histFile.write("+");
                }
                histFile.write("\n");
            }
            logFile.write( "Exiting dispHist\n");
        }
        public void copyArys(int[] ary1, int[] ary2, FileWriter logFile) throws IOException {
            logFile.write("Entering copyArys\n");
            for(int i = 0; i < ary1.length; i++){
                ary2[i] = ary1[i];
            }
            logFile.write("Exiting copyArys\n");
        }
        public void setZero(int[] ary, FileWriter logFile) throws IOException {
            logFile.write("Entering setZero\n");
            for(int i = 0; i < ary.length; i++){
               ary[i] = 0;
            }
            logFile.write("Exiting setZero\n");
        }
        public void setBlanks(char[][] graph, FileWriter logFile) throws IOException {
            logFile.write("Entering setBlanks\n");
            for(int i = 0; i < graph.length; i++){
                Arrays.fill(graph[i], '0');
            }
            logFile.write("Exiting setBlanks\n");
        }
        public int biGuassian(FileWriter logFile) throws IOException {
            logFile.write("Entering biGaussian method\n");
            double sum1, sum2, total, minSumDiff = 99999.0;
            int offset = (int)((maxVal - minVal)/10);
            int dividePt = offset;
            int bestThr = dividePt;
            while(dividePt < (maxVal - offset) ){
                setZero(GaussAry,logFile);
                sum1 = fitGauss(0, dividePt, logFile);
                sum2 = fitGauss(dividePt, maxVal, logFile);
                total = sum1 + sum2;
                if(total < minSumDiff){
                    minSumDiff = total;
                    bestThr = dividePt;
                    copyArys(GaussAry, bestFitGaussAry, logFile);
                }
                logFile.write("In biGaussian(): dividePt=" + dividePt + "\nsum1=" + sum1 +"\nsum2=" + sum2 + "\ntotal="+ total+"\nminSumDiff="+minSumDiff+"\nbestThr="+bestThr+"\n");
                dividePt++;
            }

            logFile.write("Exiting biGaussian method, minSumDiff="+minSumDiff+" bestThr="+bestThr+"\n");
            return bestThr;
        }
        public double fitGauss(int leftIndex, int rightIndex,FileWriter logFile) throws IOException {
            logFile.write("Entering fitGuass method\n");
            double mean, var, sum = 0.0, Gval;
            mean = computeMean(leftIndex, rightIndex, logFile);
            var = computeVar(leftIndex, rightIndex, mean, logFile);
            int index = leftIndex;
            while(index <= rightIndex){
                Gval = modifiedGauss(index, mean, var, logFile);
                sum += Math.abs((Gval - (double)histAry[index]));
                GaussAry[index] = (int)Gval;
                index++;
            }
            logFile.write("Exiting fitGuass method, sum is: "+ sum+"\n");
            return sum;
        }
        public double computeMean(int leftIndex, int rightIndex,FileWriter logFile) throws IOException {
            logFile.write("Entering computeMean method\n");
            int sum = 0, numPixels = 0;
            int index = leftIndex;
            while(index < rightIndex){
                sum += (histAry[index] * index);
                numPixels += histAry[index];
                if(histAry[index] > maxHeight) {
                    maxHeight = histAry[index];
                }
                index++;
            }
            double result = (double)sum /(double)numPixels;
            logFile.write("Exiting computeMean maxHeight="+maxHeight+" result="+result+"\n");
            return result;
        }
        public double computeVar(int leftIndex, int rightIndex, double mean, FileWriter logFile) throws IOException {
            logFile.write("Entering computeVar method");
            double sum = 0.0;
            int numPixels = 0;
            int index = leftIndex;
            while (index < rightIndex){
                sum += (double)histAry[index] * ((double)index - mean) * ((double)index - mean);
                numPixels += histAry[index];
                index++;
            }
            double result = sum /(double)numPixels;
            logFile.write("Exiting computeVar method returning result="+result+"\n");
            return result;
        }
        public double modifiedGauss(int x, double mean, double var, FileWriter logFile) throws IOException {
            logFile.write("Entering modifiedGauss method\n");
            double result = (double)(maxHeight * Math.exp(-Math.pow((((double)x)-mean), 2)/ (2*var)));
            logFile.write("Exiting modifiedGauss method\n");
            return result;
        }
        public void printBestFitGauss(FileWriter GaussFile, FileWriter logFile) throws IOException {
            logFile.write("Entering printBestFitGauss method\n");
            GaussFile.write(numRows +" "+numCols+" "+minVal+" "+maxVal+"\n");
            for(int i = 0; i <= maxVal; i++){
                GaussFile.write(i +" "+ GaussAry[i] + "\n");
            }
            logFile.write("Exiting printBestFitGauss\n");

        }
        public void plotGaussGraph(FileWriter logFile) throws IOException {
            logFile.write("Entering plotGaussGraph method\n");
            setBlanks(GaussGraph,logFile);
            int index = 0;
            while(index <= maxVal){
                if(bestFitGaussAry[index] > 0){
                    int i = 0;
                    while(i < bestFitGaussAry[index]) {
                        GaussGraph[index][i] = '*';
                        i++;
                    }
                }
                index++;
            }
            logFile.write("Exiting plotGaussGraph method\n");
        }
        public void dispGaussGraph(FileWriter GaussFile, FileWriter logFile) throws IOException {
            logFile.write("Entering dispGaussGraph method\n");
            for(int i = 0; i < GaussGraph.length; i++){
                for(int j = 0; j < GaussGraph[i].length; j++){
                    GaussFile.write(GaussGraph[i][j]);
                }
                GaussFile.write("\n");
            }
        }
        public void plotGapGraph(FileWriter logFile) throws IOException {
            logFile.write("Entering plotGapGraph method\n");
            setBlanks(GaussGraph,logFile);
            int index = 0;
            while(index <= maxVal){
                int end1, end2;
                if(bestFitGaussAry[index] <= histAry[index]){
                    end1 = bestFitGaussAry[index];
                    end2 = histAry[index];
                }else{
                    end1 = histAry[index];
                    end2 = bestFitGaussAry[index];
                }
                int i = end1;
                while(i <= end2){
                    gapGraph[index][i] = '@';
                    i++;
                }
                index++;
            }
            logFile.write("Leaving plotGapGraph method\n");
        }
        public void dispGapGraph(FileWriter GaussFile, FileWriter logFile) throws IOException {
            logFile.write("Entering dispGapGraph method\n");
            for(int i = 0; i < gapGraph.length; i++){
                for(int j = 0; j < gapGraph[i].length; j++){
                    GaussFile.write(gapGraph[i][j]);
                }
                GaussFile.write("\n");
            }
        }
    }


    public static void main(String[] args) throws IOException {
        InputStream a1 = new FileInputStream(args[0]);
        Scanner inFile1 = new Scanner(a1);
        FileWriter histFile , GaussFile, logFile;
        histFile = new FileWriter(args[1]);
        GaussFile = new FileWriter(args[2]);
        logFile = new FileWriter(args[3]);

        BiMeans bi = new BiMeans(inFile1.nextInt(), inFile1.nextInt(), inFile1.nextInt(), inFile1.nextInt(), logFile);
        bi.histHeight = bi.loadHist(inFile1, logFile);
        bi.GaussGraph = new char[bi.maxVal+1][bi.histHeight+1];
        bi.gapGraph = new char[bi.maxVal+1][bi.histHeight+1];
        bi.setBlanks(bi.GaussGraph, logFile);
        bi.setBlanks(bi.gapGraph, logFile);

        histFile.write("** Below is the graphic display of the input histogram **\n");
        bi.printHist(logFile, histFile);
        histFile.write("** Below is the graphic display of the input histogram **\n");
        bi.dispHist(logFile, histFile);

        bi.BiGaussThrVal = bi.biGuassian(logFile);
        GaussFile.write("** The selected threshold value is "+bi.BiGaussThrVal+"\n");
        GaussFile.write("** Below is the best Fitted Gaussians **\n");
        bi.printBestFitGauss(GaussFile, logFile);

        bi.plotGaussGraph(logFile);
        GaussFile.write("** Below is the graphic display of BestFitGaussAry **\n");
        GaussFile.write(bi.numRows +" "+bi.numCols+" "+ bi.minVal +" "+ bi.maxVal +"\n");
        bi.dispGaussGraph(GaussFile, logFile);

        bi.plotGapGraph(logFile);
        GaussFile.write("** Below displays the gaps between the histogram and the best fitted Gaussians **\n");
        GaussFile.write(bi.numRows +" "+bi.numCols+" "+ bi.minVal +" "+ bi.maxVal +"\n");
        bi.dispGapGraph(GaussFile, logFile);

        logFile.write("Closing Files");
        inFile1.close();
        histFile.close();
        GaussFile.close();
        logFile.close();
    }
}
