/*
  This program implements a conversion from a .pgm image file to a terminal
  representation of the image using ASCII characters.
*/
//------------------------------------------------------------------------------

#include "file_functions.hpp"         //GetFileSize, GetImageSize
#include "data_treat_functions.hpp"   //GetPixelGrayscales, CreateAgglutinatedPixelMatrix,
                                      //PopulateAgglutinatedPixelMatrix
#include "drawing_functions.hpp"       //DrawImageInTextFile
//------------------------------------------------------------------------------

int main(){
  int const MAX_WIDTH{400}; //This should be an user input

  std::fstream image_file("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize file_size{GetFileSize(image_file)};

  std::vector<char> file_data{ReadFileData(image_file, file_size)};

  ImageSize image_size{GetImageSize(file_data)};

  std::vector<int> pixel_grayscales{GetPixelGrayscales(file_data)};

  std::vector<std::vector<AgglutinatedPixel>> agglutinated_pixel_matrix
  {CreateAgglutinatedPixelMatrix(MAX_WIDTH, image_size)};

  PopulateAgglutinatedPixelMatrix(agglutinated_pixel_matrix, pixel_grayscales, image_size);

  std::vector<std::string> agglutinated_pixels_as_char{MapPixelToChar()};

  DrawImageInTextFile(agglutinated_pixel_matrix, agglutinated_pixels_as_char);

  file_data.clear();
  pixel_grayscales.clear();
  agglutinated_pixel_matrix.clear();
  agglutinated_pixels_as_char.clear();

  return 0;
}
//------------------------------------------------------------------------------
