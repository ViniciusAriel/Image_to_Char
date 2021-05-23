#ifndef AGGLUTINATED_PIXEL_H
#define AGGLUTINATED_PIXEL_H

#include <vector>           // std::vector

// Class represent a group os pixels of the image agglutinated together into a
// square
class AgglutinatedPixel{
public:
  AgglutinatedPixel();
  ~AgglutinatedPixel();

  void AddGrayscaleValue(int pixel);

  int GetMeanGrayscaleValue();

private:
  std::vector<int>* pixel_grayscales;
};

#endif
