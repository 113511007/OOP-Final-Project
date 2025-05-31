#include <iostream> 
#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"
#include "image_encryption.h"
#include "bit_field_filter.h"

using namespace std;

void printMenu() {
  cout << "\n--- Image Processing Demo ---\n";
  cout << "1. Load and display grayscale image\n";
  cout << "2. Load and display RGB image\n";
  cout << "3. Apply flip filters\n";
  cout << "4. Apply mosaic filters\n";
  cout << "5. Apply Gaussian filters\n";
  cout << "6. Apply Laplacian filters\n";
  cout << "7. Encode secret message\n";
  cout << "8. Decode secret message\n";
  cout << "0. Exit\n";
  cout << "Enter your choice: ";
}

int main() {
  Image* image = nullptr;
  bool running = true;
  int choice;

  while(running) {
    printMenu();
    cin >> choice;
    switch(choice) {
      case 1: {
	string gray_filename;
	cout << "Enter the filename: ";
	cin >> gray_filename;
        image = new GrayImage();
        image->LoadImage(gray_filename);
        image->DumpImage("output_gray.png");
        image->Display_CMD();
        break;
      }
      case 2: {
	string rgb_filename;
        cout << "Enter the filename: ";
        cin >> rgb_filename;
        image = new RGBImage();
        image->LoadImage(rgb_filename);
        image->DumpImage("output_rgb.png");
        image->Display_CMD();
        break;
      }
      case 3: {
        if(image) {
          uint8_t options = FILTER_FLIP;
          applyFilters(*image, options);
          image->DumpImage("flip_filtered.png");
          image->Display_CMD();
        } 
	else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 4: {
        if(image) {
          uint8_t options = FILTER_MOSAIC;
          applyFilters(*image, options);
          image->DumpImage("mosaic_filtered.png");
          image->Display_CMD();
        }
        else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 5: {
        if(image) {
          uint8_t options = FILTER_GAUSSIAN;
          applyFilters(*image, options);
          image->DumpImage("Gaussian_filtered.png");
          image->Display_CMD();
        }
        else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 6: {
        if(image) {
          uint8_t options = FILTER_LAPLACIAN;
          applyFilters(*image, options);
          image->DumpImage("Laplacian_filtered.png");
          image->Display_CMD();
        }
        else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 7: {
        if(image) {          
          string secret;
	  cout << "Enter the secret to be encoded: ";
          cin >> secret;
	  ImageEncryption::encode(image, secret);
          image->DumpImage("encoded.png");
        } 
	else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 8: {
        if(image) {
          string decoded = ImageEncryption::decode(image);
          cout << "Decoded message: " << decoded << endl;
        } 
	else {
          cout << "Please load an image first.\n";
        }
        break;
      }
      case 0: {
        running = false;
        break;
      }
      default:
        cout << "Invalid option.\n";
    }
  }

  delete image;
  return 0;
}
