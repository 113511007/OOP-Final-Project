#include "main_function.h"
using namespace std;

void main_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  int choice;
  do {
    display_title();
    cout << "=================================\n";
    cout << "1. Load Images\n";
    cout << "2. Enter Command Mode\n";
    cout << "3. Exit System\n";
    cout << "Enter option: ";
    cin >> choice;

    switch(choice) {
      case 1:
        load_image_menu(loaded_images, image_names);
        break;
      case 2:
        command_mode_menu(loaded_images, image_names);
        break;
      case 3:
        cout << "Exiting system...\n";
        return;
      default:
        cout << "Invalid option. Please try again.\n";
        press_enter_to_continue();
    }
  } while(true);
}

void command_mode_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  if (loaded_images.empty()) {
    cout << "No images loaded. Please load images first.\n";
    press_enter_to_continue();
    return;
  }

  int choice;
  do {
    display_title();
    cout << "=================================\n";
    cout << "Current loaded images:\n";
    for (size_t i = 0; i < loaded_images.size(); ++i) {
      cout << i+1 << ". " << image_names[i] << " ("
           << loaded_images[i]->get_width() << "x"
           << loaded_images[i]->get_height() << " "
           << (loaded_images[i]->get_channels() == 1 ? "Grayscale" : "RGB")
           << ")\n";
    }
    cout << "=================================\n";
    cout << "1. Image Analysis Tools\n";
    cout << "2. Filter Processing\n";
    cout << "3. Image Encryption\n";
    cout << "4. Save and Return\n";
    cout << "Enter option: ";
    cin >> choice;

    switch(choice) {
      case 1:
        image_analysis_menu(loaded_images, image_names);
        break;
      case 2:
        filter_menu(loaded_images, image_names);
        break;
      case 3:
        encryption_menu(loaded_images, image_names);
        break;
      case 4:
        save_and_return(loaded_images, image_names);
        return;
      default:
        cout << "Invalid option. Please try again.\n";
        press_enter_to_continue();
    }
  }
  while(true);
}

void save_and_return(vector<Image*>& loaded_images, vector<string>& image_names) {
  for (size_t i = 0; i < loaded_images.size(); ++i) {
    loaded_images[i]->DumpImage(image_names[i]);
    cout << "Image saved as: " << image_names[i] << "\n";
  }
  press_enter_to_continue();
}
