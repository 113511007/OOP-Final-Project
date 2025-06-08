#include "image_steganography.h"
#include <vector>
#include <string>
#include <algorithm>
#include <stdexcept>
using namespace std;

namespace {

vector<bool> stringToBits(const string& message) {
  vector<bool> bits;
  
  uint32_t len = message.size() * 8;
  for (int i = 31; i >= 0; --i) {
    bits.push_back((len >> i) & 1);
  }

  for (char c : message) {
    for (int i = 7; i >= 0; --i) {
      bits.push_back((c >> i) & 1);
    }
  }
  return bits;
}

string bitsToString(const vector<bool>& bits) {
  if (bits.size() < 32) return "";
  uint32_t len = 0;
  for (int i = 0; i < 32; ++i) {
    len |= bits[i] << (31 - i);
  }

  if (len + 32 > bits.size()) return "";

  string message;
  for (size_t i = 32; i + 8 <= bits.size() && message.size() < len / 8; i += 8) {
    char c = 0;
    for (int j = 0; j < 8; ++j) {
      c |= bits[i + j] << (7 - j);
    }
    message += c;
  }
  return message;
}

void lsbEncrypt(Image* image, const string& message) {
  vector<bool> bits = stringToBits(message);
  int width = image->get_width();
  int height = image->get_height();
  int channels = image->get_channels();

  size_t bit_pos = 0;
  if (channels == 1) {
    int** pixels = image->gray_get_pixels();
    for (int y = 0; y < height && bit_pos < bits.size(); ++y) {
      for (int x = 0; x < width && bit_pos < bits.size(); ++x) {
        pixels[y][x] = (pixels[y][x] & 0xFE) | bits[bit_pos++];
      }
    }
  } 
  else {
    int*** pixels = image->rgb_get_pixels();
    for (int y = 0; y < height && bit_pos < bits.size(); ++y) {
      for (int x = 0; x < width && bit_pos < bits.size(); ++x) {
        for (int c = 0; c < channels && bit_pos < bits.size(); ++c) {
          pixels[y][x][c] = (pixels[y][x][c] & 0xFE) | bits[bit_pos++];
        }
      }
    }
  }
}

string lsbDecrypt(Image* image) {
  int width = image->get_width();
  int height = image->get_height();
  int channels = image->get_channels();

  vector<bool> bits;
  if (channels == 1) {
    int** pixels = image->gray_get_pixels();
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        bits.push_back(pixels[y][x] & 1);
      }
    }
  } 
  else {
    int*** pixels = image->rgb_get_pixels();
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        for (int c = 0; c < channels; ++c) {
          bits.push_back(pixels[y][x][c] & 1);
        }
      }
    }
  }
  return bitsToString(bits);
}

void bitplaneEncrypt(Image* image, const string& message) {
  vector<bool> bits = stringToBits(message);
  int width = image->get_width();
  int height = image->get_height();
  int channels = image->get_channels();

  size_t bit_pos = 0;
  if (channels == 1) {
    int** pixels = image->gray_get_pixels();
    for (int y = 0; y < height && bit_pos < bits.size(); ++y) {
      for (int x = 0; x < width && bit_pos < bits.size(); ++x) {
        pixels[y][x] = (pixels[y][x] & ~(1 << 0)) | (bits[bit_pos++] << 0);
      }
    }
  } 
  else {
    int*** pixels = image->rgb_get_pixels();
    for (int y = 0; y < height && bit_pos < bits.size(); ++y) {
      for (int x = 0; x < width && bit_pos < bits.size(); ++x) {
        for (int c = 0; c < channels && bit_pos < bits.size(); ++c) {
          pixels[y][x][c] = (pixels[y][x][c] & ~(1 << 0)) | (bits[bit_pos++] << 0);
        }
      }
    }
  }
}

string bitplaneDecrypt(Image* image) {
  int width = image->get_width();
  int height = image->get_height();
  int channels = image->get_channels();

  vector<bool> bits;
  if (channels == 1) {
    int** pixels = image->gray_get_pixels();
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        bits.push_back((pixels[y][x] >> 0) & 1);
      }
    }
  } 
  else {
    int*** pixels = image->rgb_get_pixels();
    for (int y = 0; y < height; ++y) {
      for (int x = 0; x < width; ++x) {
        for (int c = 0; c < channels; ++c) {
          bits.push_back((pixels[y][x][c] >> 0) & 1);
        }
      }
    }
  }
  return bitsToString(bits);
} 

}

void applyEncryption(Image* image, uint8_t options, const string& message) { 
  if (options & EN_LSB) { 
    lsbEncrypt(image, message); 
  } 
  if (options & EN_BITPLANE) { 
    bitplaneEncrypt(image, message); 
  }  
} 

string applyDecryption(Image* image, uint8_t options) { 
  if (options & DE_LSB) { 
    return lsbDecrypt(image); 
  } 
  if (options & DE_BITPLANE) { 
    return bitplaneDecrypt(image); 
  } 
  return "No valid decryption method selected.";
}