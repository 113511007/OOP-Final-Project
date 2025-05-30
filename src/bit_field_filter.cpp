#include "bit_field_filter.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

void applyFilters(Image& image, uint8_t options) {
  if(options & FILTER_FLIP) horizontalFlip(image);
  if(options & FILTER_MOSAIC) mosaic(image);
  if(options & FILTER_GAUSSIAN) gaussianBlur(image);
  if(options & FILTER_LAPLACIAN) laplacianSharpen(image);
}

void horizontalFlip(Image& image) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channels();
  if(channels == 1) {
    int** pixels = image.gray_get_pixels();
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width / 2; j++) {
	swap(pixels[i][j], pixels[i][width - 1 - j]);
      }
    }
  }
  else {
    int*** pixels = image.rgb_get_pixels();
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width / 2; j++) {
        for (int k = 0; k < channels; k++) {
          swap(pixels[i][j][k], pixels[i][width - 1 - j][k]);
        }
      }
    }
  }
}

void mosaic(Image& image) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channels();
  int blockSize = 5;
  if(channels == 1) {
    int** pixels = image.gray_get_pixels();
    for(int i = 0; i < height; i += blockSize) {
      for(int j = 0; j < width; j += blockSize) {
        int sum = 0, count = 0;
        for(int bi = i; bi < min(i + blockSize, height); bi++) {
          for(int bj = j; bj < min(j + blockSize, width); bj++) {
            sum += pixels[bi][bj];
            count++;
          }
        }
        int avg = sum / count;        
        for(int bi = i; bi < min(i + blockSize, height); bi++) {
          for(int bj = j; bj < min(j + blockSize, width); bj++) {
            pixels[bi][bj] = avg;
          }
        }
      }
    }
  }
  else {
    int*** pixels = image.rgb_get_pixels();
    for(int i = 0; i < height; i += blockSize) {
      for(int j = 0; j < width; j += blockSize) {
        int sum[3] = {0}, count = 0;
        for(int bi = i; bi < min(i + blockSize, height); bi++) {
          for(int bj = j; bj < min(j + blockSize, width); bj++) {
             for(int k = 0; k < channels; k++) {
               sum[k] += pixels[bi][bj][k];
             }
             count++;
           }
        }
        int avg[3] = {sum[0]/count, sum[1]/count, sum[2]/count};
        for(int bi = i; bi < min(i + blockSize, height); bi++) {
          for(int bj = j; bj < min(j + blockSize, width); bj++) {
            for(int k = 0; k < channels; k++) {
              pixels[bi][bj][k] = avg[k];
            }
          }
        }
      }
    }
  }
}

void gaussianBlur(Image& image) {
  const double SD = 1.0;
  const int radius = static_cast<int>(std::ceil(3 * SD));
  const int size = 2 * radius + 1;
  std::vector<std::vector<double>> kernel(size, std::vector<double>(size));
  double sum = 0.0;
  for(int i = -radius; i <= radius; ++i) {
    for(int j = -radius; j <= radius; ++j) {
      double value = exp(-(i * i + j * j) / (2 * SD * SD)) / (2 * M_PI * SD * SD);
      kernel[i + radius][j + radius] = value;
      sum += value;
    }
  }
  for(auto& row : kernel) {
    for(auto& v : row) {
      v /= sum;
    }
  }
  applyKernel(image, kernel);
}

void laplacianSharpen(Image& image) {
  vector<vector<double>> kernel = {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}};
  applyKernel(image, kernel);
}


void applyKernel(Image& image, const vector<vector<double>>& kernel) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channels();
  int kSize = kernel.size();
  int kRadius = kSize / 2;
  if(channels == 1) {
    int** pixels = image.gray_get_pixels();
    int** temp = new int* [height];
    for (int i = 0; i < height; i++) {
      temp[i] = new int [width];
      for(int j = 0; j < width; j++) {
        double sum = 0;
        for(int ki = -kRadius; ki <= kRadius; ki++) {
          for(int kj = -kRadius; kj <= kRadius; kj++) {
            int ni = i + ki;
            int nj = j + kj;
            if(ni >= 0 && ni < height && nj >= 0 && nj < width) {
              sum += kernel[ki + kRadius][kj + kRadius] * pixels[ni][nj];
            }
          }
        }
      if(sum < 0) {temp[i][j] = 0;}
      else if(sum > 255) {temp[i][j] = 255;}
      else {temp[i][j] = static_cast<int>(sum);}
      }
    } 
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        pixels[i][j] = temp[i][j];
      }
      delete [] temp[i];
    }
    delete [] temp;
  }
  else {
    int*** pixels = image.rgb_get_pixels();
    int*** temp = new int** [height];
    for (int i = 0; i < height; i++) {
      temp[i] = new int* [width];
      for(int j = 0; j < width; j++) {
        temp[i][j] = new int [channels];
        for(int k = 0; k < channels; k++) {
          double sum = 0;
          for(int ki = -kRadius; ki <= kRadius; ki++) {
            for(int kj = -kRadius; kj <= kRadius; kj++) {
              int ni = i + ki;
              int nj = j + kj;
              if(ni >= 0 && ni < height && nj >= 0 && nj < width) {
                sum += kernel[ki + kRadius][kj + kRadius] * pixels[ni][nj][k];
              }
            }
          }
          if(sum < 0) {temp[i][j][k] = 0;}
          else if(sum > 255) {temp[i][j][k] = 255;}
          else {temp[i][j][k] = static_cast<int>(sum);}
        }
      }
    } 
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        for(int k = 0; k < channels; k++) {
          pixels[i][j][k] = temp[i][j][k];
        }
        delete [] temp[i][j];
      }
      delete [] temp[i];
    }
    delete [] temp;
  }
}
