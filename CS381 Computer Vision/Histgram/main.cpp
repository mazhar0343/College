#include <iostream>
#include <string>
#include <iostream>
#include <fstream>

using namespace std;

class img{
  public:
    int numRows;
    int numCols;
    int minVal;
    int maxVal;
    int* histAry;
    int** imgAry;
    int thrVal;
   
    void loadimage(ifstream &data, ofstream &logFile){
      logFile << "Entering loadimage" << endl;
      while(!data.eof()){
        for(int i = 0; i < numRows; i++){
          for(int j = 0; j < numCols; j++){
            data >> imgAry[i][j];
          }
        }
      }
      logFile << "Exiting loadimage" << endl;
    }

    void computeHist(ofstream &logFile){
      logFile << "Entering computeHist" << endl;
      for(int i = 0; i < numRows; i++){
        for(int j = 0; j < numCols; j++){
          int val = imgAry[i][j];
          if(val < minVal || val > maxVal){
            logFile << imgAry [i][j] << "value is not within minVal and maxVal" << endl;
            exit(1);
          }
          histAry[val]++;
        }
      }
      logFile << "Exiting computeHist" << endl;
    }

    void printHist(ofstream &histCount, ofstream &logFile){
      logFile << "Entering printHist" << endl;
      for(int i = 0; i <= maxVal; i++){
        histCount << i << " " << histAry[i] << endl;
      }
      logFile << "Exiting printHist" << endl;
    }

    void dispHist(ofstream &histGraph, ofstream &logFile){
      logFile << "Entering dispHist" << endl;
      for(int i = 0; i <= maxVal; i++){
          histGraph << i << " (" << histAry[i] << "):";
        for(int j = 0; j < histAry[i]; j++){
            histGraph << "+";
        }
          histGraph << endl;
      }
      logFile << "Exiting dispHist" << endl;
    }

    void binaryThershold(ofstream &binaryThr, ofstream &logFile){
      logFile << "Entering binaryThershold" << endl;
      logFile << "The result of the binary thresholding using " << thrVal <<" as threshold value" << endl;

      binaryThr << numRows << " " << numCols << " " << 0 << " " << 1 << endl;
      logFile << numRows << " " << numCols << " " << 0 << " " << 1 << endl;

      for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
          if (imgAry[i][j] >= thrVal){
            binaryThr << 1 << " ";
            logFile << 1 << " ";
          }else{
            binaryThr << 0 << " ";
            logFile << 0 << " ";
          }
        }
        binaryThr << endl;
        logFile << endl;
      }

      logFile << "Exiting binaryThershold" << endl;
    }

    void PrettyPrint(ofstream &logFile){
      logFile << "Entering PrettyPrint" << endl;
      logFile << numRows << " " << numCols << " " << minVal << " " << maxVal << endl;

      string val = to_string(maxVal);
      int Width = val.length();
      
      for (int i = 0; i < numRows; i++){
        for (int j = 0; j < numCols; j++){
          logFile << imgAry[i][j];
          string w = to_string(imgAry[i][j]);
          int ww = w.length();        
          while(ww <= Width){
            logFile <<" ";
            ww++;
          }
        }
        logFile << endl;
    } 
      logFile << endl << "Leaving PrettyPrint" << endl;
    }
};


int main(int argc, char *argv[]) {
  img image;
  
  ifstream data;
  ofstream histCountFile, histGraphFile, binThrFile, logFile;

  data.open(argv[1]);
  histCountFile.open(argv[3]);
  histGraphFile.open(argv[4]);
  binThrFile.open(argv[5]);
  logFile.open(argv[6]);
  
  if(!data.is_open()){
    cout << "Error Opening File" << endl;
  }
  if(!histCountFile.is_open()){
    cout << "Error Opening HistCount File" << endl;
  }
  if(!histGraphFile.is_open()){
    cout << "Error Opening HistGraph File" << endl;
  }
  if(!binThrFile.is_open()){
    cout << "Error Opening BinThr File" << endl;
  }
  if(!logFile.is_open()){
    cout << "Error Opening logFile File" << endl;
  }
  logFile << "Opened all files"<< endl;

  data >> image.numRows >> image.numCols >> image.minVal >> image.maxVal;
  logFile << "Rows: " << image.numRows << endl << "Cols: " << image.numCols << endl <<"Min: " << image.minVal << endl << "Max:" << image.maxVal << endl;


  image.imgAry = new int*[image.numRows];
  for(int i = 0; i < image.numRows; i++){
    image.imgAry[i] = new int[image.numCols];
  }
  logFile << "Created imgAry" << endl;

  image.loadimage(data, logFile);
  image.PrettyPrint(logFile);

  logFile << "Creating histAry" << endl;
  image.histAry = new int[image.maxVal+1];
  for(int i = 0; i <= image.maxVal; i++){
    image.histAry[i] = 0;
  }
  logFile << "Created histAry" << endl;

  image.computeHist(logFile);
  image.printHist(histCountFile, logFile);
  image.dispHist(histGraphFile, logFile);

  image.thrVal = atoi(argv[2]);
  logFile << "The threshold value is : " << image.thrVal << endl;
  
  image.binaryThershold(binThrFile, logFile);
  
  logFile << "Closing all files" << endl;
  data.close();
  histCountFile.close();
  histGraphFile.close();
  binThrFile.close();
  logFile.close();
}