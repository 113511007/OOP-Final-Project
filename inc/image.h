#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <string>
#include "data_loader.h"
using namespace std;

class Image{
protected:
  int width;
  int height;
  int channels;
  Data_Loader loader;
public:
  Image(int theWidth, int theHeight, int theChannels);
  ~Image();
  virtual bool LoadImage(string filename);
  virtual void DumpImage(string filename);
  virtual void Display_X_Server();
  virtual void Display_ASCII();
  virtual void Display_CMD();
  int get_width();
  int get_height();
  int get_channels();
  virtual int** gray_get_pixels();
  virtual int*** rgb_get_pixels();
};

#endif
