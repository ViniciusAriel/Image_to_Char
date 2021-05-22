#include "data_treat_functions.hpp"

std::vector<int> GetPixelGrayscales(std::vector<char>& file_data){
  std::vector<int> pixel_grayscales;
  std::bitset<8> char_as_binary;
  for(int i{0}; i < file_data.size(); ++i){
    char_as_binary = std::bitset<8>(file_data[i]);
    pixel_grayscales.push_back((int)(char_as_binary.to_ulong()));
  }

  return pixel_grayscales;
}

// Calculate how many sized elements fit into an extent, rounding up
int CalculateElementsPerExtent(int extent_size, int element_size){
  int number_of_elements;
  if(extent_size % element_size == 0){
    number_of_elements = (int) (extent_size / element_size);
  }
  else{
    number_of_elements = (int) ((extent_size / element_size) + 1);
  }

  return number_of_elements;
}

AgglutinatedImage CreateAgglutinatedImage
(int const& MAX_WIDTH, ImageSize& image_size){

  // Quantity of pixels a Agglutinated Pixel square contains in its side
  int side_size_in_pixels{CalculateElementsPerExtent(image_size.width, MAX_WIDTH)};

  // Quantity of Agglutinated Pixels to exist in a single row
  int aglt_pixels_per_row{CalculateElementsPerExtent(image_size.width, side_size_in_pixels)};

  // Quantity of Agglutinated Pixels to exist in a single column
  int aglt_pixels_per_col{CalculateElementsPerExtent(image_size.height, side_size_in_pixels)};

  AgglutinatedImage aglt_image(side_size_in_pixels, aglt_pixels_per_row, aglt_pixels_per_col);

  return aglt_image;
}
