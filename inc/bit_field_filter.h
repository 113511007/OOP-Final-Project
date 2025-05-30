#ifndef BIT_FIELD_FILTER_H
#define BIT_FIELD_FILTER_H

#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include <cstdint>
#define FILTER_FLIP       0x01
#define FILTER_MOSAIC     0x02
#define FILTER_GAUSSIAN   0x04
#define FILTER_LAPLACIAN  0x08

void applyFilters(Image& image, uint8_t options);
void horizontalFlip(Image& image);
void mosaic(Image& image);
void gaussianBlur(Image& image);
void laplacianSharpen(Image& image);
void applyKernel(Image& image, const vector<vector<double>>& kernel);

#endif