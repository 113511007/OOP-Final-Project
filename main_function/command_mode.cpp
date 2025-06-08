#include "main_function.h"
#include <sys/stat.h>
#include <libgen.h>

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
    cout << "3. Image Encryption (Steganography)\n";
    cout << "4. Image Decryption (Steganography)\n";
    cout << "5. Image Encryption (Cryptography)\n";
    cout << "6. Image Decryption (Cryptography)\n";
    cout << "7. Save and Return\n";
    cout << "8. Remove an Image\n";
    cout << "9. Clear All Images\n";
    cout << "Enter option: ";
    cin >> choice;

    bool decrypt = (choice == 4 || choice == 6);

    switch(choice) {
      case 1:
        image_analysis_menu(loaded_images, image_names);
        break;
      case 2:
        filter_menu(loaded_images, image_names);
        break;
      case 3: case 4:
        steganography_menu(loaded_images, image_names, decrypt);
        break;
      case 5: case 6:
        cryptography_menu(loaded_images, image_names, decrypt);
        break;
      case 7:
        save_and_return(loaded_images, image_names);
        return;
      case 8: {
        int index;
        cout << "Enter the number of the image to remove: ";
        cin >> index;
        if (index >= 1 && index <= static_cast<int>(loaded_images.size())) {
          delete loaded_images[index - 1];
          loaded_images.erase(loaded_images.begin() + index - 1);
          image_names.erase(image_names.begin() + index - 1);
          cout << "Image removed.\n";
        } else {
          cout << "Invalid index.\n";
        }
        press_enter_to_continue();
        break;
      }
      case 9:
        for (Image* img : loaded_images) {
          delete img;
        }
        loaded_images.clear();
        image_names.clear();
        cout << "All loaded images have been cleared.\n";
        press_enter_to_continue();
        return;
      default:
        cout << "Invalid option. Please try again.\n";
        press_enter_to_continue();
    }
  }
  while(true);
}