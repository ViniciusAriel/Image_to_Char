#include "drawing_functions.hpp"

std::vector<std::string> MapPixelToChar(){
  std::vector<std::string> pixels_as_char;

  pixels_as_char.push_back("█");
  pixels_as_char.push_back("▓");
  pixels_as_char.push_back("▒");
  pixels_as_char.push_back(" ");

  return pixels_as_char;
}

void DrawImageInTextFile(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix,
std::vector<std::string> pixels_as_char){

   float threshold_value{255.0 / 4.0};
   std::fstream text_file("Text.txt", std::ios_base::out);

   for(int j{0}; j < agglutinated_pixel_matrix.size(); ++j){
     text_file << '\n';
     for(int i{0}; i < agglutinated_pixel_matrix[j].size(); ++i){

       text_file << pixels_as_char[(int)(agglutinated_pixel_matrix[j][i].GetMeanGrayScaleValue() / threshold_value)];
     }
   }

   text_file.close();
 }
