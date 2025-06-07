#ifndef IMAGE_ENCRYPTION_H
#define IMAGE_ENCRYPTION_H

#include "image.h"
#include <string>
#include <vector>
using namespace std;

#define ENCRYPT_LSB          0x01
#define DECRYPT_LSB          0x02
#define ENCRYPT_XOR          0x04
#define ENCRYPT_CAESAR       0x08
#define ENCRYPT_SUBSTITUTION 0x16

void applyEncryption(Image* image, uint8_t options, const string& message, const string& key, int shift, const vector<int>& table);

#endif