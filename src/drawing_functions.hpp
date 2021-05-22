#include <vector>                   //std::vector
#include <fstream>                  //std::fstream, std::ios_base
#include "agglutinated_pixel.hpp"   //Class: AgglutinatedPixel
#include "agglutinated_image.hpp"

std::vector<std::string> MapPixelToChar();

void DrawImageInTextFile(AgglutinatedImage& aglt_image, std::vector<std::string> pixels_as_char);
