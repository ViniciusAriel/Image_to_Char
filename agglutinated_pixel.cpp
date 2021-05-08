#include "agglutinated_pixel.h"

AgglutinatedPixel::AgglutinatedPixel(){
  pixels = new std::vector<int>();
}

AgglutinatedPixel::~AgglutinatedPixel(){
  delete pixels;
}

void AgglutinatedPixel::AddPixel(int pixel){
  pixels->push_back(pixel);
}

std::vector<int> AgglutinatedPixel::GetPixels(){
  return *pixels;
}

int AgglutinatedPixel::GetMeanPixelValue(){
  int mean{0};
  for(int pixel : *pixels){
    mean += pixel;
  }
  mean /= pixels->size();
  return mean;
}
