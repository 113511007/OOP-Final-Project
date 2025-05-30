#include "rgb_image.h"
using namespace std;

RGBImage::RGBImage(): Image(0, 0, 0), pixels(nullptr) {}
RGBImage::RGBImage(int theWidth, int theHeight, int*** thePixels): Image(theWidth, theHeight, 3) {
  pixels = new int** [theHeight];
  for(int i = 0; i < theHeight; i++) {
    pixels[i] = new int* [theWidth];
    for(int j = 0; j < theWidth; j++) {
      pixels[i][j] = new int [3];
      for(int k = 0; k < 3; k++) {
        pixels[i][j][k] = thePixels[i][j][k];
      }
    }
  }
}
RGBImage::~RGBImage() {
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      delete [] pixels[i][j];
    }
    delete [] pixels[i];
  }
  delete [] pixels;
}

bool RGBImage::LoadImage(string filename) {
  int*** loaded_pixels = loader.Load_RGB(filename, &width, &height);    
  if(!loaded_pixels) {
    cerr << "Failed to load RGB image: " << filename << endl;
    return false;
  }
  if(pixels) {
    for(int i = 0; i < height; i++) {
      for(int j = 0; j < width; j++) {
        delete [] pixels[i][j];
      }
      delete [] pixels[i];
    }
    delete [] pixels;
  }
  pixels = new int** [height];
  for(int i = 0; i < height; i++) {
    pixels[i] = new int* [width];
    for(int j = 0; j < width; j++) {
      pixels[i][j] = new int [3];
      for(int k = 0; k < 3; k++) {
        pixels[i][j][k] = loaded_pixels[i][j][k];
      }
    }
  }
  for(int i = 0; i < height; i++) {
    for(int j = 0; j < width; j++) {
      delete [] loaded_pixels[i][j];
    }
    delete [] loaded_pixels[i];
  }
  delete[] loaded_pixels;
  return true;
}

void RGBImage::DumpImage(string filename) {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions");   
  loader.Dump_RGB(width, height, pixels, filename);
}

void RGBImage::Display_X_Server() {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions");
  loader.Display_RGB_X_Server(width, height, pixels);
}

void RGBImage::Display_ASCII() {
  assert(pixels != nullptr && "Pixel data is null");
  assert(width > 0 && height > 0 && "Invalid image dimensions"); 
  loader.Display_RGB_ASCII(width, height, pixels);
}

void RGBImage::Display_CMD() {}

int*** RGBImage::rgb_get_pixels() {return pixels;}