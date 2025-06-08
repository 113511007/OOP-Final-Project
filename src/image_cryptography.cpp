#include "image_cryptography.h"
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace {

  void xorEncrypt(Image* image, const string& key) {
    if (key.empty()) return;
    int width = image->get_width();
    int height = image->get_height();
    int channels = image->get_channels();        
    if (channels == 1) {
      int** pixels = image->gray_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          char k = key[(y * width + x) % key.length()];
          pixels[y][x] ^= static_cast<int>(k);
        }
      }
    }
    else {
      int*** pixels = image->rgb_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          char k = key[(y * width + x) % key.length()];
          for(int ch = 0; ch < channels; ch++) {
            pixels[y][x][ch] ^= static_cast<int>(k);
          }
        }
      }
    }
  }

  void caesarEncrypt(Image* image, int shift) {        
    int width = image->get_width();
    int height = image->get_height();
    int channels = image->get_channels();    
    if (channels == 1) {
      int** pixels = image->gray_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          pixels[y][x] = (pixels[y][x] + shift + 256) % 256;
        }
      }
    } 
    else {
      int*** pixels = image->rgb_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          for(int ch = 0; ch < channels; ch++) {
            pixels[y][x][ch] = (pixels[y][x][ch] + shift + 256) % 256;
          }
        }
      }
    }
  }
  
  void substitutionEncrypt(Image* image, const vector<int>& table) {
    if (!image || table.size() != 256) return;    
    int width = image->get_width();
    int height = image->get_height();
    int channels = image->get_channels();        
    if (channels == 1) {
      int** pixels = image->gray_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          pixels[y][x] = table[pixels[y][x]];
        }
      }
    } 
    else {
      int*** pixels = image->rgb_get_pixels();
      for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
          for(int ch = 0; ch < channels; ch++) {
            pixels[y][x][ch] = table[pixels[y][x][ch]];
          }
        }
      }
    }
  }
  
}

void applyEncryption(Image* image, uint8_t options, const string& key, int shift, const vector<int>& table) {
  if (options & USE_XOR && !key.empty()) {
    xorEncrypt(image, key);
  }
  if (options & USE_CAESAR) {
    caesarEncrypt(image, shift);
  }
  if (options & USE_SUBSTITUTION) {
    substitutionEncrypt(image, table);
  }
}