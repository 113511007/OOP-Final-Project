#include "gray_image.h"
using namespace std;

GrayImage::GrayImage(): Image(0, 0, 1), pixels(nullptr) {}
GrayImage::GrayImage(int theWidth, int theHeight, int** thePixels): Image(theWidth, theHeight, 1) {
  pixels = new int* [theHeight];
  for(int i = 0; i < theHeight; i++) {
    pixels[i] = new int [theWidth];
    for(int j = 0; j < theWidth; j++) {
      pixels[i][j] = thePixels[i][j];
    }
  }
}
GrayImage::~GrayImage() {
  for(int i = 0; i < height; i++) {
    delete [] pixels[i];
  }
  delete [] pixels;
}

bool GrayImage::LoadImage(string filename) {
  int** loaded_pixels = loader.Load_Gray(filename, &width, &height);    
  if(!loaded_pixels) {
    cerr << "Failed to load gray image: " << filename << endl;
    return false;
  }
  if(pixels) {
    for (int i = 0; i < height; ++i) {
      delete[] pixels[i];
    }
    delete[] pixels;
  }
  pixels = new int*[height];
  for (int i = 0; i < height; ++i) {
    pixels[i] = new int[width];
    for (int j = 0; j < width; ++j) {
      pixels[i][j] = loaded_pixels[i][j];
    }
  }
  for (int i = 0; i < height; ++i) {
        delete[] loaded_pixels[i];
  }
  delete[] loaded_pixels;
  return true;
}

void GrayImage::DumpImage(string filename) {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions");   
  loader.Dump_Gray(width, height, pixels, filename);
}

void GrayImage::Display_X_Server() {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions");
  loader.Display_Gray_X_Server(width, height, pixels);
}

void GrayImage::Display_ASCII() {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions"); 
  loader.Display_Gray_ASCII(width, height, pixels);
}

void GrayImage::Display_CMD() {}

int** GrayImage::gray_get_pixels() {return pixels;}
