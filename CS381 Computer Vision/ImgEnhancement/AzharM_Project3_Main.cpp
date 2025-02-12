#include <iostream>
#include <string>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

class Enhancement{
    public:
        int numRows;
        int numCols;
        int minVal;
        int maxVal;
        int maskRows;
        int maskCols;
        int maskMin;
        int maskMax;
        int newMin;
        int newMax;
        int thrVal;
        int** mirrorFmAry;
        int** avgAry;
        int** medianAry;
        int** GaussAry;
        int** thrAry;
        int** mask2DAry;
        int mask1DAry[9];
        int maskWeight;
        int neighbor1DAry[9];

        void binThreshold(int** inAry, int** outAry, ofstream &logFile){

          for(int i = 0; i < numRows; i++){
            for(int j = 0; j < numCols; j++){
              if(inAry[i][j] >= thrVal){
                outAry[i][j] = 1;
              }
              else{
                outAry[i][j] = 0;
              }
            }
          }
        }

        void prettyPrint(int** arr, ofstream &oFile, ofstream &logFile){
          logFile << "Entering PrettyPrint" << endl;
          oFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

          string val = to_string(maxVal);
          int Width = val.length();
          
          for (int i = 0; i <= numRows; i++){
            for (int j = 0; j <= numCols; j++){
              oFile << arr[i][j];
              string w = to_string(arr[i][j]);
              int ww = w.length();        
              while(ww <= Width){
                oFile <<" ";
                ww++;
              }
            }
            oFile << endl;
          } 
          logFile <<"Leaving PrettyPrint" << endl;
      }

        void mirrorFraming(ofstream &logFile){
          logFile << "Entering Mirror Framing" << endl;
          for(int i = 1; i <= numCols; i++){
            mirrorFmAry[0][i] = mirrorFmAry[1][i];
          }
          for(int i = 1; i <= numCols; i++){
            mirrorFmAry[numRows+1][i] = mirrorFmAry[numRows][i];
          }

          for(int i = 0; i <= numRows+1; i++){
            mirrorFmAry[i][0] = mirrorFmAry[i][1];
          }
          for(int i = 0; i <= numRows+1; i++){
            mirrorFmAry[i][numCols+1] = mirrorFmAry[i][numCols];
          }

          logFile << "Exiting Mirror Framing" << endl;
        }

        void loadImage(ifstream &inFile, ofstream &logFile){
          logFile << "Entering loadImage" << endl;
          for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
              inFile >> mirrorFmAry[i][j];
            }
          }
          
          logFile << "Exiting loadImage()" << endl;
        }

        int loadMask(ifstream &maskFile, ofstream &logFile){
          logFile << "Entering loadMask" << endl;
          int sum = 0;
          for(int i = 0; i < maskRows; i++){
            for(int j = 0; j < maskCols; j++){
              maskFile >> mask2DAry[i][j];
              sum += mask2DAry[i][j];
            }
          }

          logFile << "Exiting loadMask" << endl;
          return sum;
        }

        void loadMask2Dto1D(ofstream &logFile){
          logFile << "Entering loadMask2Dto1D" << endl;
          int counter = 0;
          for(int i = 0; i < maskRows; i++){
            for(int j = 0; j < maskCols; j++){
              mask1DAry[counter] = mask2DAry[i][j];
              counter++;
            }
          }
          logFile << "Exiting loadMask2Dto1D" << endl;
        }

        void loadNeighbor2Dto1D(int i, int j, ofstream &logFile){
          logFile << "Entering loadNeighbor2Dto1D" << endl;
          
          neighbor1DAry[0] = mirrorFmAry[i-1][j-1];
          neighbor1DAry[1] = mirrorFmAry[i-1][j];
          neighbor1DAry[2] = mirrorFmAry[i-1][j+1];
          neighbor1DAry[3] = mirrorFmAry[i][j-1];
          neighbor1DAry[4] = mirrorFmAry[i][j];
          neighbor1DAry[5] = mirrorFmAry[i][j+1];
          neighbor1DAry[6] = mirrorFmAry[i+1][j-1];
          neighbor1DAry[7] = mirrorFmAry[i+1][j];
          neighbor1DAry[8] = mirrorFmAry[i+1][j+1];
          
          logFile << "Exiting loadNeighbor2Dto1D" << endl;
        }

        void sort(ofstream &logFile){
          logFile << "Entering sort" << endl;
          std::sort(neighbor1DAry, neighbor1DAry+9);
          logFile << "Exiting sort" << endl;
        }

        void computeMedian(ofstream &logFile){
          logFile << "Entering computeMedian" << endl;
          
          newMin = 9999;
          newMax = 0;

          int i = 1; 

          while(i <= numRows){
            int j = 1;
  
            while(j <= numCols){
              loadNeighbor2Dto1D(i, j, logFile);
              logFile << "** Below is conversion of mirrorFmAry [" <<i << "][" << j <<"] to 1D array" << endl;
              printAry(neighbor1DAry, logFile);
              logFile << "** Below is the sorted neighbor array i: " << i << " j: " << j << endl;
              sort(logFile);
                printAry(neighbor1DAry, logFile);
              medianAry[i][j] = neighbor1DAry[4];
              if(newMin > medianAry[i][j]){
                newMin = medianAry[i][j];
              }
              if(newMax < medianAry[i][j]){
                newMax = medianAry[i][j];
              }
              j++;
            }
            i++;
          }
          logFile << "Exiting computeMedian" << endl;
        }

        void computeAvg(ofstream &logFile){
          logFile << "Entering computeAvg" << endl;
          for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
              loadNeighbor2Dto1D(i, j, logFile);
              int sum = 0;
              for(int i = 0; i < 9; i++){
                sum += neighbor1DAry[i];
              }
              avgAry[i][j] = sum/9;
            }
          }
            logFile << "Exiting computeAvg" << endl;
        }

        void computeGauss(ofstream &logFile){
          logFile << "Entering computeGauss" << endl;
          int newMin = 9999, newMax = 0;
          for(int i = 1; i <= numRows; i++){
            for(int j = 1; j <= numCols; j++){
              loadNeighbor2Dto1D(i, j, logFile);
              logFile << "** Below is conversion of mirrorFmAry [" << i << "]["<< j << "] to 1D array" << endl;
                printAry(neighbor1DAry,logFile);
              logFile << "** Below is the mask1DAry i: " << i <<" j: "<< j << endl;
                printAry(mask1DAry,logFile);
              GaussAry[i][j] = convolution(logFile);
              if(newMin > GaussAry[i][j]){
                newMin = GaussAry[i][j];
              }
              if(newMax < GaussAry[i][j]){
                newMax = GaussAry[i][j];
              }
            }
          }
          logFile << "Exiting computeGauss" << endl;
        }

        int convolution(ofstream &logFile){
          logFile << "Entering convolution" << endl;
          int result = 0;
          for(int i = 0; i < 9; i++){
            result += mask1DAry[i] * neighbor1DAry[i];
          }
          result = result / maskWeight;
          logFile << "Leaving convolution method, convolution maskWeight = "<< result << endl;
          return result;
        }

        void printAry(int* arr, ofstream &oFile){
          for(int i = 0; i < 9; i++){
            oFile << arr[i] << " ";
          }
          oFile << endl;
        }
        void printAry(int** arr, ofstream &oFile){
          for(int i = 0; i < maskRows; i++){
            for(int j = 0; j < maskCols; j++){
              oFile << arr[i][j] << " ";
            }
            oFile << endl;
          }
        }
};

int main(int argc, char *argv[]){
  ifstream inFile, maskFile;
  ofstream AvgFile, MedianFile, GaussFile, logFile;
  inFile.open(argv[1]);
  maskFile.open(argv[2]);
  AvgFile.open("AvgFile.txt");
  MedianFile.open("MedianFile.txt");
  GaussFile.open("GaussFile.txt");
  logFile.open("logFile.txt");

  if(!inFile.is_open()){
    cout << "InFile not open" << endl;
  }
  if(!maskFile.is_open()){
    cout << "MaskFile not open" << endl;
  }
  if(!AvgFile.is_open()){
    cout << "AvgFile not open" << endl;
  }
  if(!MedianFile.is_open()){
    cout << "MedianFile not open" << endl;
  }
  if(!GaussFile.is_open()){
    cout << "GaussFile not open" << endl;
  }
  if(!logFile.is_open()){
    cout << "logFile not open" << endl;
  }

  Enhancement e;

  inFile >> e.numRows >> e.numCols >> e.minVal >> e.maxVal;
  maskFile >> e.maskRows >> e.maskCols >> e.maskMin >> e.maskMax;

  e.thrVal = atoi(argv[3]);

  e.mirrorFmAry = new int*[e.numRows+2];
  for(int i = 0; i < e.numRows+2; i++){
      e.mirrorFmAry[i] = new int[e.numCols+2];
  }
  
  e.avgAry = new int*[e.numRows+2];
  for(int i = 0; i < e.numRows+2; i++){
      e.avgAry[i] = new int[e.numCols+2];
  }
  
  e.medianAry = new int*[e.numRows+2];
  for(int i = 0; i < e.numRows+2; i++){
      e.medianAry[i] = new int[e.numCols+2];
  }
  
  e.GaussAry = new int*[e.numRows+2];
  for(int i = 0; i < e.numRows+2; i++){
      e.GaussAry[i] = new int[e.numCols+2];
  }
  
  e.thrAry = new int*[e.numRows+2];
  for(int i = 0; i < e.numRows+2; i++){
      e.thrAry[i] = new int[e.numCols+2];
  }
  
  e.mask2DAry = new int*[e.maskRows];
  for(int i = 0; i < e.maskRows; i++){
      e.mask2DAry[i] = new int[e.maskCols];
  }

  e.maskWeight = e.loadMask(maskFile, logFile);

  e.loadMask2Dto1D(logFile);

  e.loadImage(inFile, logFile);

  e.mirrorFraming(logFile);

  AvgFile << "** Below is the mirror framed input image. ***" << endl;
  e.prettyPrint(e.mirrorFmAry, AvgFile, logFile);
  e.computeAvg(logFile);
  AvgFile << "**  Below is the 3x3 averaging of the input image. ***" << endl;
  e.prettyPrint(e.avgAry, AvgFile, logFile);
  e.binThreshold(e.avgAry, e.thrAry, logFile);
  AvgFile << "** Below is the result of the binary threshold of averaging image. ***" << endl;
  e.prettyPrint(e.thrAry, AvgFile, logFile);
  
  MedianFile << "** Below is the mirror framed input image. ***" << endl;
  e.prettyPrint(e.mirrorFmAry, MedianFile, logFile);
  e.computeMedian(logFile);
  MedianFile << "** Below is the 3x3 median filter of the input image. **" << endl;
  e.prettyPrint(e.medianAry, MedianFile, logFile);
  MedianFile << "** Below is the result of the binary threshold of median filtered image. ***" << endl;
  e.prettyPrint(e.thrAry, MedianFile, logFile);

  GaussFile << "** Below is the mirror framed input image. ***" << endl;
  e.prettyPrint(e.mirrorFmAry, GaussFile, logFile);
  GaussFile << "** Below is the mask for Gaussian filer. **" << endl;
  e.printAry(e.mask2DAry, GaussFile);
  e.computeGauss(logFile);
  GaussFile << "** Below is the 3x3 gaussian filter of the input image. ***" << endl;
  e.prettyPrint(e.GaussAry, GaussFile, logFile);
  e.binThreshold(e.medianAry, e.thrAry, logFile);
  GaussFile << "** Below is the result of the binary threshold of gaussian filtered image. ***" << endl;
  e.prettyPrint(e.thrAry, GaussFile, logFile);


  inFile.close();
  maskFile.close();
  AvgFile.close();
  MedianFile.close();
  GaussFile.close();
  logFile << "All Files Closed";
  logFile.close();
}