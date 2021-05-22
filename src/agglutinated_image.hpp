#ifndef AGGLUTINATED_IMAGE_H
#define AGGLUTINATED_IMAGE_H

#include <vector>                  // std::vector
#include "image_size.hpp"          // Struct: ImageSize
#include "agglutinated_pixel.hpp"  // Class: AgglutinatedPixel

class AgglutinatedImage{
public:
  AgglutinatedImage(int aglt_pixel_side_size, int aglt_pixels_per_row, int aglt_pixels_per_col);
  ~AgglutinatedImage();

  int GetAgglutinatedPixelsPerRow();
  int GetAgglutinatedPixelsPerCol();

  void PopulateAgglutinatedImage(std::vector<int>& pixel_grayscales, ImageSize& image_size);

  int GetAgglutinatedPixelsMeanGrayscaleValue(int row, int col);

private:
  int aglt_pixel_side_size;
  int aglt_pixels_per_row;
  int aglt_pixels_per_col;
  std::vector<std::vector<AgglutinatedPixel>>* aglt_pixel_matrix;
};


#endif
