/*
  This program implements a conversion from a .pgm image file to a terminal
  representation of the image using ASCII characters.
*/
//------------------------------------------------------------------------------

#include "file_functions.hpp"         //GetFileSize, GetImageSize
#include "data_treat_functions.hpp"   //GetPixelGrayscales, CreateAgglutinatedPixelMatrix,
                                      //PopulateAgglutinatedPixelMatrix
#include "drawing_function.hpp"       //DrawImageInTextFile
//------------------------------------------------------------------------------

int main(){
  int const MAX_WIDTH{400}; //This should be an user input

  std::fstream image_file("capivara.pgm", std::ios_base::in | std::ios_base::binary);

  std::streamsize file_size{GetFileSize(image_file)};

  std::vector<char> file_data;
  file_data.resize(file_size);

  image_file.read(&file_data[0], file_size);
  image_file.close();

  ImageSize image_size{GetImageSize(file_data)};

  std::vector<int> pixel_grayscales{GetPixelGrayscales(file_data)};

  std::vector<std::vector<AgglutinatedPixel>> agglutinated_pixel_matrix
  {CreateAgglutinatedPixelMatrix(MAX_WIDTH, image_size)};

  PopulateAgglutinatedPixelMatrix(agglutinated_pixel_matrix, pixel_grayscales, image_size);

  std::vector<char> image_represented_in_char;
  DrawImageInTextFile(image_represented_in_char, agglutinated_pixel_matrix);

  file_data.clear();
  pixel_grayscales.clear();
  agglutinated_pixel_matrix.clear();

  return 0;
}
//------------------------------------------------------------------------------

//TODOS:

//Refactoring: Names. They are shitty. [DONE]
//Refactoring: put functions in other files [DONE]
//Refactoring: Tests. There are none as of now.
//Refactoring: Behaviour changes (may do this before testing)
  //Starting with a class fot the algt_pix_matrix?
//Change capybara picture!!
