#include "bit_field_filter.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

namespace {

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

void mosaic(Image& image, int mosaic_block_size) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channels();
  int blockSize = mosaic_block_size;
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

void gaussianBlur(Image& image, double gaussian_sd) {
  const double SD = gaussian_sd;
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

void fisheye(Image& image) {
  int width = image.get_width();
  int height = image.get_height();
  int*** pixels = image.rgb_get_pixels();
  int*** copy = new int**[height];
  for(int i = 0; i < height; ++i) {
    copy[i] = new int*[width];
    for(int j = 0; j < width; ++j) {
      copy[i][j] = new int[3];
      for(int k = 0; k < 3; ++k) {
        copy[i][j][k] = pixels[i][j][k];
      }
    }
  }

  double cx = width / 2.0;
  double cy = height / 2.0;
  double rmax = sqrt(cx * cx + cy * cy);

  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      double dx = x - cx;
      double dy = y - cy;
      double r = sqrt(dx * dx + dy * dy);
      double nr = r * r / rmax;
      double theta = atan2(dy, dx);
      int sx = static_cast<int>(cx + nr * cos(theta));
      int sy = static_cast<int>(cy + nr * sin(theta));
      if(sx >= 0 && sx < width && sy >= 0 && sy < height) {
        for(int k = 0; k < 3; ++k) {
          pixels[y][x][k] = copy[sy][sx][k];
        }
      }
    }
  }

  for(int i = 0; i < height; ++i) {
    for(int j = 0; j < width; ++j) {
      delete[] copy[i][j];
    }
    delete[] copy[i];
  }
  delete[] copy;
}

void coldWarmAdjust(Image& image, bool warm, int intensity, bool preserveLuminance) {
  int width = image.get_width();
  int height = image.get_height();
  int*** pixels = image.rgb_get_pixels();
    
  for(int y = 0; y < height; ++y) {
    for(int x = 0; x < width; ++x) {
      int r = pixels[y][x][0];
      int g = pixels[y][x][1];
      int b = pixels[y][x][2];
            
      double luminance = preserveLuminance ? (0.299 * r + 0.587 * g + 0.114 * b) : -1;

      if(warm) {
        r = min(255, r + intensity);
        b = max(0, b - intensity/2);
        } 
      else {
        r = max(0, r - intensity/2);
        b = min(255, b + intensity);
      }
            
      if(preserveLuminance) {
        double new_luminance = 0.299 * r + 0.587 * g + 0.114 * b;
        if(new_luminance > 0) {
          double ratio = luminance / new_luminance;
          r = min(255, static_cast<int>(r * ratio));
          g = min(255, static_cast<int>(g * ratio));
          b = min(255, static_cast<int>(b * ratio));
        }
      }
            
      pixels[y][x][0] = r;
      pixels[y][x][1] = g;
      pixels[y][x][2] = b;
    }
  }
}

void luminanceEnhance(Image& image, double luminance_scale) {
  int width = image.get_width();
  int height = image.get_height();
  int channels = image.get_channels();
  if(channels == 1) {
    int** pixels = image.gray_get_pixels();
    for(int i = 0; i < height; ++i) {
      for(int j = 0; j < width; ++j) {
        pixels[i][j] = min(255, static_cast<int>(pixels[i][j] * (1 + 0.01 * luminance_scale)));
      }
    }
  } else {
    int*** pixels = image.rgb_get_pixels();
    for(int i = 0; i < height; ++i) {
      for(int j = 0; j < width; ++j) {
        for(int k = 0; k < 3; ++k) {
          int val = static_cast<int>(pixels[i][j][k] * (1 + 0.01 * luminance_scale));
          pixels[i][j][k] = min(255, val);
        }
      }
    }
  }
}

}

void applyFilters(Image& image, uint8_t options, int mosaic_size, int gaussian_sd, int cold_intensity, bool cold_keep_lum, int warm_intensity, bool warm_keep_lum, int luminance_scale) {
  if(options & FILTER_FLIP) horizontalFlip(image);
  if(options & FILTER_MOSAIC) mosaic(image, mosaic_size);
  if(options & FILTER_GAUSSIAN) gaussianBlur(image, gaussian_sd);
  if(options & FILTER_LAPLACIAN) laplacianSharpen(image);
  if(options & FILTER_FISHEYE) fisheye(image);
  if(options & FILTER_WARM) coldWarmAdjust(image, true, warm_intensity, warm_keep_lum);
  if(options & FILTER_COLD) coldWarmAdjust(image, false, cold_intensity, cold_keep_lum);
  if(options & FILTER_LUMINANCE) luminanceEnhance(image, luminance_scale);
}