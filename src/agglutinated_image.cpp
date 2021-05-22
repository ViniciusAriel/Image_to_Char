#include "agglutinated_image.hpp"

AgglutinatedImage::AgglutinatedImage(int aglt_pixel_side_size, int aglt_pixels_per_row, int aglt_pixels_per_col){
  this->aglt_pixel_side_size = aglt_pixel_side_size;
  this->aglt_pixels_per_row = aglt_pixels_per_row;
  this->aglt_pixels_per_col = aglt_pixels_per_col;

  aglt_pixel_matrix = new std::vector<std::vector<AgglutinatedPixel>>;

  aglt_pixel_matrix->resize(aglt_pixels_per_col);
  for(int i{0}; i < aglt_pixel_matrix->size(); ++i){
    aglt_pixel_matrix->at(i).resize(aglt_pixels_per_row);
  }
}

AgglutinatedImage::~AgglutinatedImage(){
  delete aglt_pixel_matrix;
}

int AgglutinatedImage::GetAgglutinatedPixelsPerRow(){
  return aglt_pixels_per_row;
}

int AgglutinatedImage::GetAgglutinatedPixelsPerCol(){
  return aglt_pixels_per_col;
}

void AgglutinatedImage::PopulateAgglutinatedImage(std::vector<int>& pixel_grayscales, ImageSize& image_size){
  int pixel_grayscale;
  //Coordinates of the Agglutinated Pixel this Pixel will be in
  int aglt_image_row;
  int aglt_image_col;

  for(int row{0}; row < image_size.height; ++row){
    for(int col{0}; col < image_size.width; ++col){
      pixel_grayscale = pixel_grayscales[(row * image_size.width) + col];

      //Row
      aglt_image_row = (int) (row / aglt_pixel_side_size);

      //Column
      aglt_image_col = (int) (col / aglt_pixel_side_size);

      aglt_pixel_matrix->at(aglt_image_row)[aglt_image_col].AddGrayScaleValue(pixel_grayscale);
    }
  }
}

int AgglutinatedImage::GetAgglutinatedPixelsMeanGrayscaleValue(int row, int col){
  return aglt_pixel_matrix->at(row)[col].GetMeanGrayscaleValue();
}
