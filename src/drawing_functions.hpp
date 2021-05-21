#include <vector>                   //std::vector
#include <fstream>                  //std::fstream, std::ios_base
#include "agglutinated_pixel.hpp"   //Class: AgglutinatedPixel

std::vector<std::string> MapPixelToChar();

void DrawImageInTextFile(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix, std::vector<std::string> pixels_as_char);
