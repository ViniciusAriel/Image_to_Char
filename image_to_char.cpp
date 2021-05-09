/*
  This program implements a conversion from a .pgm image file to a terminal
  representation of the image using ASCII characters.
*/
//------------------------------------------------------------------------------

//Necessary Headers
#include <fstream>            //std::fstream
#include <iostream>           //std::cout, std::streamsize
#include <cstddef>
#include <vector>             //std::vector
#include <string>             //std::string
#include <limits>             //std::numeric_limits
#include <cwctype>            //iswspace
#include <bitset>             //std::bitset
#include "image.h"            //Struct: Image
#include "agglutinated_pixel.h"
//------------------------------------------------------------------------------

//Functions
std::streamsize GetFileSize(std::fstream& File){
  //Extracts (and ignores) all characters until end or file or reach max stream
  File.ignore(std::numeric_limits<std::streamsize>::max());
  //Counts charactes extracted until now
  std::streamsize FileSize{File.gcount()};
  //Clear error flags (like end of file, for example)
  File.clear();
  //Sets the position of the next character to be extracted back to the
  //beginning
  File.seekg(0, std::ios_base::beg);

  return FileSize;
}

FImage ReadImageSize(std::vector<char>& BufferData){
  bool bReadMagicNumber{false};
  std::string NumberString;

  FImage Image;

  for(int i{0}; i < BufferData.size(); ++i){
    //creates string from buffer data
    NumberString.push_back(BufferData[i]);

    //Read magic number
    if(iswspace(BufferData[i]) && !bReadMagicNumber){
      bReadMagicNumber = true;
      NumberString = "";
    }
    //Reads width
    else if(iswspace(BufferData[i]) && Image.width == 0){
      Image.width = std::atoi(NumberString.c_str());
      NumberString = "";
    }
    //Reads height
    else if(iswspace(BufferData[i]) && Image.height == 0){
      Image.height = std::atoi(NumberString.c_str());
      NumberString = "";
    }
    //Ignores the highest value for each pixel
    else if(iswspace(BufferData[i])){
      //Erases read data from buffer so we don't have to store where we left off
      BufferData.erase(BufferData.begin(), BufferData.begin() + i + 1);
      break;
    }
  }

  return Image;
}

//Returns as vector in which each int in it the greyscore value of a pixel
std::vector<int> CreatePixelBuffer(std::vector<char>& BufferData){
  std::vector<int> PixelBuffer;
  std::bitset<8> BinaryChar;
  for(int i{0}; i < BufferData.size(); ++i){
    BinaryChar = std::bitset<8>(BufferData[i]);
    PixelBuffer.push_back((int)(BinaryChar.to_ulong()));
  }

  return PixelBuffer;
}

//Creates the Agglutinated Pixel Matrix that represents the image with correct
//sizes
std::vector<std::vector<AgglutinatedPixel>> CreateAgglutinatedPixelMatrix
(int const& MAX_WIDTH, FImage& Image){
  std::vector<std::vector<AgglutinatedPixel>> AglPixMatrix;

  //Quantity of pixels a Agglutinated Pixel square contains in its side
  int AglPixSideSize;
  //When printing on the terminal, width is the limitating value
  if(Image.width % MAX_WIDTH == 0){
    AglPixSideSize = (int) (Image.width / MAX_WIDTH);
  }
  else{
    AglPixSideSize = (int) ((Image.width / MAX_WIDTH) + 1);
  }

  //Quantity of Agglutinated Pixels to exist in a single row
  int AglPixPerRow;
  if(Image.width % AglPixSideSize == 0){
    AglPixPerRow = (int) (Image.width / AglPixSideSize);
  }
  else{
    AglPixPerRow = (int) ((Image.width / AglPixSideSize) + 1);
  }

  //Quantity of Agglutinated Pixels to exist in a single column
  int AglPixPerCol;
  if(Image.height & AglPixSideSize == 0){
    AglPixPerCol = (int) (Image.height / AglPixSideSize);
  }
  else{
    AglPixPerCol = (int) ((Image.height / AglPixSideSize) + 1);
  }

  AglPixMatrix.resize(AglPixPerCol);
  for(int i{0}; i < AglPixMatrix.size(); ++i){
    AglPixMatrix[i].resize(AglPixPerRow);

    for(int j{0}; j < AglPixMatrix[i].size(); ++j){
      AglPixMatrix[i][j].SetSideSize(AglPixSideSize);
    }
  }

  return AglPixMatrix;
}

void PopulateAgglutinatedPixelMatrix
(std::vector<std::vector<AgglutinatedPixel>>& AglPixMatrix,
 std::vector<int>& PixelBuffer, FImage& Image){
   int PixelGrayScale;
   //Coordinates of the Agglutinated Pixel this Pixel will be in
   int AglPixMatrixRow;
   int AglPixMatrixCol;

   for(int row{0}; row < Image.height; ++row){
     for(int col{0}; col < Image.width; ++col){
       PixelGrayScale = PixelBuffer[(row * Image.height) + col];

       //Row
       AglPixMatrixRow = (int) (row / AglPixMatrix[0][0].GetSideSize());

       //Column
       AglPixMatrixCol = (int) (col / AglPixMatrix[0][0].GetSideSize());

       AglPixMatrix[AglPixMatrixRow][AglPixMatrixCol].AddPixel(PixelGrayScale);
     }
   }
 }
//------------------------------------------------------------------------------

//Main Program
int main(){

  int const MAX_WIDTH{120};

  std::fstream File ("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize FileSize{GetFileSize(File)};

  std::vector<char> BufferData;
  BufferData.resize(FileSize);

  File.read(&BufferData[0], FileSize);

  File.close();

  FImage Image{ReadImageSize(BufferData)};

  std::cout << Image.width << std::endl;
  std::cout << Image.height << std::endl;

  std::vector<int> PixelBuffer{CreatePixelBuffer(BufferData)};

  std::vector<std::vector<AgglutinatedPixel>> AglPixMatrix
  {CreateAgglutinatedPixelMatrix(MAX_WIDTH, Image)};

  PopulateAgglutinatedPixelMatrix(AglPixMatrix, PixelBuffer, Image);

  BufferData.clear();
  PixelBuffer.clear();
  AglPixMatrix.clear();

  return 0;
}
//------------------------------------------------------------------------------

//TODOS:
//new FImage?
//Should I really use Unreal naming conventions?
//Delete FileSize if not used anymore!
//Declare variables together?
//Fix Error: not reading file header correctly [FIXED!]
//Reading as byte [DONE]
//Logic from getting pixels? Probably new Class? [DONE!]
//Actually print image (so excited!)
