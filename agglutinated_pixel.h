#ifndef AGGLUTINATED_PIXEL_H
#define AGGLUTINATED_PIXEL_H

#include <vector>           //std::vector

//Class represent a group os pixels of the image agglutinated together into a
//square of 'side' pixels
class AgglutinatedPixel{
public:
  AgglutinatedPixel();
  ~AgglutinatedPixel();

  void AddPixel(int pixel);
  std::vector<int> GetPixels();
  int GetMeanPixelValue();

private:
  std::vector<int>* pixels;
};

#endif
