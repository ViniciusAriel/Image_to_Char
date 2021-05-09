#include "agglutinated_pixel.h"

AgglutinatedPixel::AgglutinatedPixel(){
  pixels = new std::vector<int>();
  SideSize = 0;
}

AgglutinatedPixel::~AgglutinatedPixel(){
  delete pixels;
}

void AgglutinatedPixel::AddPixel(int pixel){
  pixels->push_back(pixel);
}

void AgglutinatedPixel::SetSideSize(int s){
  SideSize = s;
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

int AgglutinatedPixel::GetSideSize(){
  return SideSize;
}
