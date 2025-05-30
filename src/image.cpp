#include "image.h"
using namespace std;

Image::Image(int theWidth, int theHeight, int theChannels): width(theWidth), height(theHeight), channels(theChannels) {}
Image::~Image() {}
bool Image::LoadImage(string filename) { return false; }
void Image::DumpImage(string filename) {}
void Image::Display_X_Server() {}
void Image::Display_ASCII() {}
void Image::Display_CMD() {}
int Image::get_width() {return width;}
int Image::get_height() {return height;}
int Image::get_channels() {return channels;}
int** Image::gray_get_pixels(){return nullptr;}
int*** Image::rgb_get_pixels(){return nullptr;}