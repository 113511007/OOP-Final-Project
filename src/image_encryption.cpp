#include "image_encryption.h"
#include <bitset>
#include <algorithm>
#include <stdexcept>

using namespace std;

namespace {

  vector<bool> stringToBits(const string& message) {
    vector<bool> bits;
    for (char c : message) {
      for (int i = 7; i >= 0; --i) {
        bits.push_back((c >> i) & 1);
      }
    }
    return bits;
  }

  string bitsToString(const vector<bool>& bits) {
    string message;
    for (size_t i = 0; i < bits.size(); i += 8) {
      char c = 0;
      for (int j = 0; j < 8 && (i + j) < bits.size(); ++j) {
        c |= bits[i + j] << (7 - j);
      }
      message += c;
    }
    return message;
  }

  bool checkCapacity(Image* image, size_t messageLength) {
    int availableBits = (image->get_width() * image->get_height() * 3) - 32;
    return (static_cast<int>(messageLength) <= availableBits);
  }

  void lsbEncode(Image* image, const string& message) {
    vector<bool> bits = stringToBits(message);
    int*** pixels = image->rgb_get_pixels();
    int width = image->get_width();
    int height = image->get_height();
    bitset<32> lenBits(bits.size());
    for(int i = 0; i < 32; ++i) {
      int x = (i / 3) % width;
      int y = (i / 3) / width;
      int ch = i % 3;
      pixels[y][x][ch] = (pixels[y][x][ch] & 0xFE) | lenBits[i];
    }
    size_t bitPos = 0;
    for(int y = 0; y < height && bitPos < bits.size(); ++y) {
      for(int x = 0; x < width && bitPos < bits.size(); ++x) {
        if(y == 0 && x < 10) continue;
        for(int ch = 0; ch < 3 && bitPos < bits.size(); ++ch) {
          pixels[y][x][ch] = (pixels[y][x][ch] & 0xFE) | bits[bitPos++];
        }
      }
    }
  }

  string lsbDecode(Image* image) {
    int*** pixels = image->rgb_get_pixels();
    int width = image->get_width();
    int height = image->get_height();
    bitset<32> lenBits;
    for(int i = 0; i < 32; ++i) {
      int x = (i / 3) % width;
      int y = (i / 3) / width;
      int ch = i % 3;
      lenBits[i] = pixels[y][x][ch] & 1;
    }
    size_t msgLength = lenBits.to_ulong();
    if(msgLength == 0 || !checkCapacity(image, msgLength)) {
      return "";
    }
    vector<bool> bits;
    for(int y = 0; y < height && bits.size() < msgLength; ++y) {
      for(int x = 0; x < width && bits.size() < msgLength; ++x) {
        if(y == 0 && x < 10) continue;
        for(int ch = 0; ch < 3 && bits.size() < msgLength; ++ch) {
          bits.push_back(pixels[y][x][ch] & 1);
        }
      }
    }
    return bitsToString(bits);
  }

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

void applyEncryption(Image* image, uint8_t options, const string& message, const string& key, int shift, const vector<int>& table) {
  if (!image) return;
  if (options & ENCRYPT_LSB & !message.empty()) {
    lsbEncode(image, message);
  } 
  else if (options & DECRYPT_LSB){
    string decoded = lsbDecode(image);
    cout << "Decoded LSB message: " << decoded << endl;
  }
  if (options & ENCRYPT_XOR && !key.empty()) {
    xorEncrypt(image, key);
  }
  if (options & ENCRYPT_CAESAR) {
    caesarEncrypt(image, shift);
  }
  if (options & ENCRYPT_SUBSTITUTION) {
    substitutionEncrypt(image, table);
  }
}