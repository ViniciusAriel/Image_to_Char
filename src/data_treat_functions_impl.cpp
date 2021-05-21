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

std::vector<std::vector<AgglutinatedPixel>> CreateAgglutinatedPixelMatrix
(int const& MAX_WIDTH, ImageSize& image_size){

  // Quantity of pixels a Agglutinated Pixel square contains in its side
  int side_size_in_pixels{CalculateElementsPerExtent(image_size.width, MAX_WIDTH)};

  // Quantity of Agglutinated Pixels to exist in a single row
  int aglt_pixels_per_row{CalculateElementsPerExtent(image_size.width, side_size_in_pixels)};

  // Quantity of Agglutinated Pixels to exist in a single column
  int aglt_pixels_per_col{CalculateElementsPerExtent(image_size.height, side_size_in_pixels)};

  std::vector<std::vector<AgglutinatedPixel>> aglt_pixel_matrix;

  aglt_pixel_matrix.resize(aglt_pixels_per_col);
  for(int i{0}; i < aglt_pixel_matrix.size(); ++i){
    aglt_pixel_matrix[i].resize(aglt_pixels_per_row);

    for(int j{0}; j < aglt_pixel_matrix[i].size(); ++j){
      aglt_pixel_matrix[i][j].SetSideSizeInPixels(side_size_in_pixels);
    }
  }

  return aglt_pixel_matrix;
}

void PopulateAgglutinatedPixelMatrix
(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix,
 std::vector<int>& pixel_grayscales, ImageSize& image_size){

   int PixelGrayScale;
   //Coordinates of the Agglutinated Pixel this Pixel will be in
   int agglutinated_pixel_matrixRow;
   int agglutinated_pixel_matrixCol;

   for(int row{0}; row < image_size.height; ++row){
     for(int col{0}; col < image_size.width; ++col){
       PixelGrayScale = pixel_grayscales[(row * image_size.width) + col];

       //Row
       agglutinated_pixel_matrixRow = (int) (row / agglutinated_pixel_matrix[0][0].GetSideSizeInPixels());

       //Column
       agglutinated_pixel_matrixCol = (int) (col / agglutinated_pixel_matrix[0][0].GetSideSizeInPixels());

       agglutinated_pixel_matrix[agglutinated_pixel_matrixRow][agglutinated_pixel_matrixCol].AddGrayScaleValue(PixelGrayScale);
     }
   }
 }
