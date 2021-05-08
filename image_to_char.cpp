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
  //Clear flags (like end of file, for example)
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
    if(BufferData[i] == '\n' && !bReadMagicNumber){
      std::cout << "1: " << NumberString << std::endl;
      bReadMagicNumber = true;
      NumberString = "";
    }
    //Reads width
    else if(BufferData[i] == ' ' && Image.width == 0){
      std::cout << "2: " << NumberString << std::endl;
      Image.width = std::atoi(NumberString.c_str());
      BufferData.erase(BufferData.begin(), BufferData.begin() + i + 1);
      NumberString = "";
    }
    //Reads height
    else if(BufferData[i] == '\n' && Image.height == 0){
      std::cout << "3: " << NumberString << std::endl;
      Image.height = std::atoi(NumberString.c_str());
      BufferData.erase(BufferData.begin(), BufferData.begin() + i + 1);
      NumberString = "";
    }
    else if(BufferData[i] == '\n'){
      std::cout << "4: " << NumberString << std::endl;
      BufferData.erase(BufferData.begin(), BufferData.begin() + i + 1);
      break;
    }
  }

  return Image;
}
//------------------------------------------------------------------------------

//Main Program
int main(){

  std::fstream File ("capivara.pgm", std::ios_base::in /*| std::ios_base::binary*/);

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
//Fix Error: not reading file header correctly