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
#include "image.h"            //Struct: Image
#include <cwctype>            //iswspace
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
//------------------------------------------------------------------------------

//Main Program
int main(){

  std::fstream File ("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize FileSize{GetFileSize(File)};

  std::vector<char> BufferData;
  BufferData.resize(FileSize);

  File.read(&BufferData[0], FileSize);

  FImage Image{ReadImageSize(BufferData)};

  std::cout << Image.width << std::endl;
  std::cout << Image.height << std::endl;

  File.close();
  BufferData.clear();

  return 0;
}
//------------------------------------------------------------------------------

//TODOS:
//new FImage?
//Should I really use Unreal naming conventions?
//Fix Error: not reading file header correctly [FIXED!]
//Logic from getting pixels? Probablye new Class?
