#ifndef AGGLUTINATED_PIXEL_H
#define AGGLUTINATED_PIXEL_H

#include <vector>           //std::vector

//Class represent a group os pixels of the image agglutinated together into a
//square
class AgglutinatedPixel{
public:
  AgglutinatedPixel();
  ~AgglutinatedPixel();

  void AddGrayScaleValue(int pixel);
  void SetSideSizeInPixels(int s);

  int GetMeanGrayScaleValue();
  int GetSideSizeInPixels();

private:
  std::vector<int>* pixel_grayscales;
  int side_size_in_pixels;
};

#endif
