#include "drawing_function.hpp"

void DrawImageInTextFile(std::vector<std::vector<AgglutinatedPixel>>& agglutinated_pixel_matrix){

   float threshold_value{255.0 / 4.0};
   std::fstream text_file("Text.txt", std::ios_base::out);

   for(int j{0}; j < agglutinated_pixel_matrix.size(); ++j){
     text_file << '\n';
     for(int i{0}; i < agglutinated_pixel_matrix[j].size(); ++i){
       if(agglutinated_pixel_matrix[j][i].GetMeanGrayScaleValue() < threshold_value){
         text_file << "█";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanGrayScaleValue() < 2 * threshold_value){
         text_file << "▓";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanGrayScaleValue() < 3 * threshold_value){
         text_file << "▒";
       }
       else if(agglutinated_pixel_matrix[j][i].GetMeanGrayScaleValue() < 4 * threshold_value){
         text_file << ' ';
       }
     }
   }

   text_file.close();
 }
