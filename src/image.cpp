#include "image.h"
using namespace std;

Image::Image(int theWidth, int theHeight, int theChannels): width(theWidth), height(theHeight), channels(theChannels) {}
Image::~Image() {}
int Image::get_width() {return width;}
int Image::get_height() {return height;}
int Image::get_channels() {return channels;}
int** Image::gray_get_pixels(){return nullptr;}
int*** Image::rgb_get_pixels(){return nullptr;}