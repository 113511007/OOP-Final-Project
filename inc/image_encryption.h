#ifndef _IMAGE_ENCRYPTION_H_
#define _IMAGE_ENCRYPTION_H_
#include <string>
#include <vector>
#include "rgb_image.h"
using namespace std;

class ImageEncryption{
public:
  static bool encode(Image* image, string& message);
  static string decode(Image* image);

private:
  static vector<bool> stringToBits(std::string& message);
  static string bitsToString(vector<bool>& bits);
  static bool checkCapacity(Image* image, size_t messageLength);
};

#endif