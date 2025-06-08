#ifndef IMAGE_STEGANOGRAPHY_H
#define IMAGE_STEGANOGRAPHY_H

#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <cstdint>

#define EN_LSB      0x1
#define EN_BITPLANE 0x2
#define DE_LSB      0x4
#define DE_BITPLANE 0x8

void applyEncryption(Image* image, uint8_t options, const std::string& message);
std::string applyDecryption(Image* image, uint8_t options);

#endif