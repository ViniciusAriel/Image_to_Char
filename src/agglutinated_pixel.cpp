#include "agglutinated_pixel.hpp"

AgglutinatedPixel::AgglutinatedPixel(){
  pixel_grayscales = new std::vector<int>();
  side_size_in_pixels = 0;
}

AgglutinatedPixel::~AgglutinatedPixel(){
  delete pixel_grayscales;
}

void AgglutinatedPixel::AddGrayScaleValue(int grayscale_value){
  pixel_grayscales->push_back(grayscale_value);
}

void AgglutinatedPixel::SetSideSizeInPixels(int s){
  side_size_in_pixels = s;
}

int AgglutinatedPixel::GetMeanGrayScaleValue(){
  int mean{0};
  for(int grayscale : *pixel_grayscales){
    mean += grayscale;
  }
  mean /= pixel_grayscales->size();
  return mean;
}

int AgglutinatedPixel::GetSideSizeInPixels(){
  return side_size_in_pixels;
}
