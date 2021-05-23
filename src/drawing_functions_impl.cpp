#include "drawing_functions.hpp"
#include <iostream>
std::vector<std::string> DefineTextFileChars(){
  std::vector<std::string> chars;

  chars.push_back("█");
  chars.push_back("▓");
  chars.push_back("▒");
  chars.push_back(" ");

  return chars;
}

void DrawImageInTextFile(AgglutinatedImage& aglt_image,
std::vector<std::string> chars){

   float threshold_value{255.0 / 4.0};
   std::fstream text_file("Text.txt", std::ios_base::out);

   for(int j{0}; j < aglt_image.GetAgglutinatedPixelsPerCol(); ++j){
     text_file << '\n';
     for(int i{0}; i < aglt_image.GetAgglutinatedPixelsPerRow(); ++i){

       text_file << chars[(int)(aglt_image.GetAgglutinatedPixelsMeanGrayscaleValue(j, i) / threshold_value)];
     }
   }

   text_file.close();
 }
