/*
  This program implements a conversion from a .pgm image file to a terminal
  representation of the image using ASCII characters.
*/
//------------------------------------------------------------------------------

//Necessary Headers
#include <fstream>                //std::fstream
#include <iostream>               //std::cout, std::streamsize
#include <vector>                 //std::vector
#include <string>                 //std::string
#include <limits>                 //std::numeric_limits
#include <cwctype>                //iswspace
#include <bitset>                 //std::bitset
#include "image.hpp"              //Struct: Image
#include "agglutinated_pixel.hpp" //Class: AgglutinatedPixel
//------------------------------------------------------------------------------

//Functions
std::streamsize GetFileSize(std::fstream& file){
  //Extracts (and ignores) all characters until end or file or reach max stream
  file.ignore(std::numeric_limits<std::streamsize>::max());
  //Counts charactes extracted until now
  std::streamsize file_size{file.gcount()};
  //Clear error flags (like end of file, for example)
  file.clear();
  //Sets the position of the next character to be extracted back to the
  //beginning
  file.seekg(0, std::ios_base::beg);

  return file_size;
}

Image ReadImageHeader(std::vector<char>& file_data){
  bool magic_number_read{false};
  std::string number_string;

  Image image;

  for(int i{0}; i < file_data.size(); ++i){
    //creates string from buffer data
    number_string.push_back(file_data[i]);

    //Read magic number
    if(iswspace(file_data[i]) && !magic_number_read){
      magic_number_read = true;
      number_string = "";
    }
    //Reads width
    else if(iswspace(file_data[i]) && image.width == 0){
      image.width = std::atoi(number_string.c_str());
      number_string = "";
    }
    //Reads height
    else if(iswspace(file_data[i]) && image.height == 0){
      image.height = std::atoi(number_string.c_str());
      number_string = "";
    }
    //Ignores the highest value for each pixel
    else if(iswspace(file_data[i])){
      //Erases read data from buffer so we don't have to store where we left off
      file_data.erase(file_data.begin(), file_data.begin() + i + 1);
      break;
    }
  }

  return image;
}

std::vector<int> GetPixelGrayscales(std::vector<char>& file_data){
  std::vector<int> pixel_grayscales;
  std::bitset<8> char_as_binary;
  for(int i{0}; i < file_data.size(); ++i){
    char_as_binary = std::bitset<8>(file_data[i]);
    pixel_grayscales.push_back((int)(char_as_binary.to_ulong()));
  }

  return pixel_grayscales;
}

std::vector<std::vector<AgglutinatedPixel>> CreateAgglutinatedPixelMatrix
(int const& MAX_WIDTH, Image& image){

  //Quantity of pixels a Agglutinated Pixel square contains in its side
  int side_size_in_pixels;
  //When printing on the terminal, width is the limitating value
  if(image.width % MAX_WIDTH == 0){
    side_size_in_pixels = (int) (image.width / MAX_WIDTH);
  }
  else{
    side_size_in_pixels = (int) ((image.width / MAX_WIDTH) + 1);
  }

  //Quantity of Agglutinated Pixels to exist in a single row
  int aglt_pixels_per_row;
  if(image.width % side_size_in_pixels == 0){
    aglt_pixels_per_row = (int) (image.width / side_size_in_pixels);
  }
  else{
    aglt_pixels_per_row = (int) ((image.width / side_size_in_pixels) + 1);
  }

  //Quantity of Agglutinated Pixels to exist in a single column
  int aglt_pixels_per_col;
  if(image.height & side_size_in_pixels == 0){
    aglt_pixels_per_col = (int) (image.height / side_size_in_pixels);
  }
  else{
    aglt_pixels_per_col = (int) ((image.height / side_size_in_pixels) + 1);
  }

  std::vector<std::vector<AgglutinatedPixel>> aglt_pixel_matrix;

  aglt_pixel_matrix.resize(aglt_pixels_per_col);
  for(int i{0}; i < aglt_pixel_matrix.size(); ++i){
    aglt_pixel_matrix[i].resize(aglt_pixels_per_row);

    for(int j{0}; j < aglt_pixel_matrix[i].size(); ++j){
      aglt_pixel_matrix[i][j].SetSideSize(side_size_in_pixels);
    }
  }

  return aglt_pixel_matrix;
}

void PopulateAgglutinatedPixelMatrix
(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix,
 std::vector<int>& pixel_grayscales, Image& image){
   int PixelGrayScale;
   //Coordinates of the Agglutinated Pixel this Pixel will be in
   int agglutinated_pixel_matrixRow;
   int agglutinated_pixel_matrixCol;

   for(int row{0}; row < image.height; ++row){
     for(int col{0}; col < image.width; ++col){
       PixelGrayScale = pixel_grayscales[(row * image.width) + col];

       //Row
       agglutinated_pixel_matrixRow = (int) (row / agglutinated_pixel_matrix[0][0].GetSideSize());

       //Column
       agglutinated_pixel_matrixCol = (int) (col / agglutinated_pixel_matrix[0][0].GetSideSize());

       agglutinated_pixel_matrix[agglutinated_pixel_matrixRow][agglutinated_pixel_matrixCol].AddPixel(PixelGrayScale);
     }
   }
 }

 void ConvertImageToChar(std::vector<char>& image_represented_in_char,
 std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix){

   float threshold_value{255.0 / 4.0};
   std::fstream text_file("Text.txt", std::ios_base::out);

   for(int j{0}; j < agglutinated_pixel_matrix.size(); ++j){
     text_file << '\n';
     for(int i{0}; i < agglutinated_pixel_matrix[j].size(); ++i){
       if(agglutinated_pixel_matrix[j][i].GetMeanPixelValue() < threshold_value){
         text_file << "█";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanPixelValue() < 2 * threshold_value){
         text_file << "▓";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanPixelValue() < 3 * threshold_value){
         text_file << "▒";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanPixelValue() < 4 * threshold_value){
         text_file << ' ';
       }
     }
   }

   text_file.close();
 }
//------------------------------------------------------------------------------

//Main Program
int main(){
  int const MAX_WIDTH{400};

  std::fstream image_file("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize file_size{GetFileSize(image_file)};

  std::vector<char> file_data;
  file_data.resize(file_size);

  image_file.read(&file_data[0], file_size);
  image_file.close();

  Image image{ReadImageHeader(file_data)};

  std::vector<int> pixel_grayscales{GetPixelGrayscales(file_data)};

  std::vector<std::vector<AgglutinatedPixel>> agglutinated_pixel_matrix
  {CreateAgglutinatedPixelMatrix(MAX_WIDTH, image)};

  PopulateAgglutinatedPixelMatrix(agglutinated_pixel_matrix, pixel_grayscales, image);

  std::vector<char> image_represented_in_char;
  ConvertImageToChar(image_represented_in_char, agglutinated_pixel_matrix);

  file_data.clear();
  pixel_grayscales.clear();
  agglutinated_pixel_matrix.clear();

  return 0;
}
//------------------------------------------------------------------------------

//TODOS:

//Refactoring: Names. They are shitty. [DONE]
//Refactoring: Tests. There are none as of now.
//Refactoring: Behaviour changes (may do this before testing)
  //Starting with a class fot the algt_pix_matrix?
//Change capybara picture!!
