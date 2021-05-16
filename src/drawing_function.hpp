#include <vector>                   //std::vector
#include <fstream>                  //std::fstream, std::ios_base
#include "agglutinated_pixel.hpp"   //Class: AgglutinatedPixel

void DrawImageInTextFile(std::vector<char>& image_represented_in_char,
std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix);
