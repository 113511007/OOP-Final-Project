#include "image.h"
using namespace std;

Image::Image(int theWidth, int theHeight): width(theWidth), height(theHeight) {}
Image::~Image() {}
int Image::get_width() {return width;}
int Image::get_height() {return height;}
