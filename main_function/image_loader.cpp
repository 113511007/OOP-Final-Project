#include "main_function.h"
using namespace std;

void load_image_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  string filename;
  do {
    display_title();
    cout << "=================================\n";
    if (loaded_images.size() == 0) {
      cout << "No images loaded.\n";
    }
    else {
      cout << "Current loaded images:\n";
      for (size_t i = 0; i < loaded_images.size(); ++i) {
        cout << i+1 << ". " << image_names[i] << " (" 
          << loaded_images[i]->get_width() << "x" 
          << loaded_images[i]->get_height() << " "
          << (loaded_images[i]->get_channels() == 1 ? "Grayscale" : "RGB")
          << ")\n";
      }
    }
    cout << "=================================\n";
    cout << "Enter image filename (or 'q' to go back): ";
    cin >> filename;

    if (filename == "q") {
      return;
    }

    // Try to load the image
    Image* new_image;
    if (filename.find(".jpg") != string::npos || filename.find(".png") != string::npos) {
      // Try as RGB first
      new_image = new RGBImage();
      if (new_image->LoadImage(filename)) {
        loaded_images.push_back(new_image);
        image_names.push_back(filename);
        cout << "RGB image '" << filename << "' loaded successfully!\n";
      } 
      else {
        delete new_image;
        // Try as grayscale
        new_image = new GrayImage();
        if (new_image->LoadImage(filename)) {
          loaded_images.push_back(new_image);
          image_names.push_back(filename);
          cout << "Grayscale image '" << filename << "' loaded successfully!\n";
        } 
        else {
          delete new_image;
          cout << "Failed to load image '" << filename << "'\n";
        }
      }
    } 
    else {
      cout << "Unsupported file format. Please use .jpg or .png\n";
    }

    press_enter_to_continue();
  } 
  while(true);
}
