#ifndef _IMAGE_H_
#define _IMAGE_H_
#include <string>
#include "data_loader.h"
using namespace std;

class Image{
protected:
  int width;
  int height;
  Data_Loader loader;
public:
  Image(int theWidth, int theHeight);
  ~Image();
  virtual bool LoadImage(string filename);
  virtual void DumpImage(string filename);
  virtual void Display_X_Server();
  virtual void Display_ASCII();
  virtual void Display_CMD();
  int get_width();
  int get_height();
};

#endif
