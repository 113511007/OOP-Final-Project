#ifndef RGB_IMAGE_H_
#define RGB_IMAGE_H_

#include "image.h"

class RGBImage : public Image{
private:
  int*** pixels;
public:
  RGBImage();
  RGBImage(int theWidth, int theHeight, int*** thePixels);
  ~RGBImage();
  bool LoadImage(string filename);
  void DumpImage(string filename);
  void Display_X_Server();
  void Display_ASCII();
  void Display_CMD();
  int*** rgb_get_pixels();
};

#endif
