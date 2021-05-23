#include "agglutinated_pixel.hpp"

AgglutinatedPixel::AgglutinatedPixel(){
  pixel_grayscales = new std::vector<int>();
}

AgglutinatedPixel::~AgglutinatedPixel(){
  delete pixel_grayscales;
}

void AgglutinatedPixel::AddGrayscaleValue(int grayscale_value){
  pixel_grayscales->push_back(grayscale_value);
}

int AgglutinatedPixel::GetMeanGrayscaleValue(){
  int mean{0};
  for(int grayscale : *pixel_grayscales){
    mean += grayscale;
  }
  mean /= pixel_grayscales->size();
  return mean;
}
