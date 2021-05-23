/*
  This program implements a conversion from a .pgm image file to a .txt file
  representation of the image using ASCII characters.
*/
//------------------------------------------------------------------------------

#include "file_functions.hpp"         // GetFileSize, GetImageSize
#include "data_treat_functions.hpp"   // GetPixelGrayscales, CreateAgglutinatedPixelMatrix,
                                      // PopulateAgglutinatedPixelMatrix
#include "drawing_functions.hpp"      // DrawImageInTextFile
//------------------------------------------------------------------------------

int main(){
  int const MAX_WIDTH{400}; // This should be an user input

  std::fstream image_file("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize file_size{GetFileSize(image_file)};

  std::vector<char> file_data{ReadFileData(image_file, file_size)};

  ImageSize image_size{GetImageSize(file_data)};

  std::vector<int> pixel_grayscales{GetPixelGrayscales(file_data)};

  AgglutinatedImage agglutinated_image{CreateAgglutinatedImage(MAX_WIDTH, image_size)};

  agglutinated_image.PopulateAgglutinatedImage(pixel_grayscales, image_size);

  std::vector<std::string> chars_to_use{DefineTextFileChars()};

  DrawImageInTextFile(agglutinated_image, chars_to_use);

  file_data.clear();
  pixel_grayscales.clear();
  chars_to_use.clear();

  return 0;
}
//------------------------------------------------------------------------------
