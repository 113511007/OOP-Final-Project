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
#define FILTER_FISHEYE    0x10
#define FILTER_WARM       0x20
#define FILTER_COLD       0x40
#define FILTER_LUMINANCE  0x80

void applyFilters(Image& image, uint8_t options, int mosaic_block_size, double gaussian_sd, double luminance_scale);

#endif