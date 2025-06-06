#ifndef GRAY_IMAGE_H_
#define GRAY_IMAGE_H_

#include "image.h"

class GrayImage : public Image{
private:
  int** pixels;
public:
  GrayImage();
  GrayImage(int theWidth, int theHeight, int** thePixels);
  ~GrayImage();
  bool LoadImage(string filename);
  void DumpImage(string filename);
  void Display_X_Server();
  void Display_ASCII();
  void Display_CMD();
  int** gray_get_pixels();
};

#endif
