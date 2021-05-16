#include <vector>                   //std::vector
#include <bitset>                   //std::bitset
#include "image_size.hpp"           //Struct: ImageSize
#include "agglutinated_pixel.hpp"   //Class: AgglutinatedPixel

std::vector<int> GetPixelGrayscales(std::vector<char>& file_data);

std::vector<std::vector<AgglutinatedPixel>> CreateAgglutinatedPixelMatrix
(int const& MAX_WIDTH, ImageSize& image_size);

void PopulateAgglutinatedPixelMatrix
(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix,
 std::vector<int>& pixel_grayscales, ImageSize& image_size);
