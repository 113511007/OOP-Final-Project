#ifndef IMAGE_CRPTOGRAPHY_H
#define IMAGE_CRPTOGRAPHY_H

#include "image.h"
#include <string>
#include <vector>

#define USE_XOR          0x1
#define USE_CAESAR       0x2
#define USE_SUBSTITUTION 0x4

void applyEncryption(Image* image, uint8_t options, const string& key, int shift, const std::vector<int>& table);

#endif