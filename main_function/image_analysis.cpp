#include "main_function.h"
using namespace std;

void image_analysis_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  if (loaded_images.empty()) return;
  int img_choice = 1;
  if (loaded_images.size() > 1) {
    cout << "Select image (1-" << loaded_images.size() << "): ";
    cin >> img_choice;
    if (img_choice < 1 || img_choice > static_cast<int>(loaded_images.size())) {
      cout << "Invalid image selection.\n";
      press_enter_to_continue();
      return;
    }
  }
  Image* img = loaded_images[img_choice-1];
  
  int choice;
  do {
    display_title();
    cout << "=================================\n";
    cout << "Image Analysis: " << image_names[img_choice-1] << "\n";
    cout << "=================================\n";
    cout << "1. Display in X Server\n";
    cout << "2. Display in ASCII\n";
    cout << "3. Display in CMD\n";
    cout << "4. Return to previous menu\n";
    cout << "Enter option: ";
    cin >> choice;

    switch(choice) {
      case 1:
        img->Display_X_Server();
        break;
      case 2:
        img->Display_ASCII();
        break;
      case 3:
        img->Display_CMD();
        break;
      case 4:
        return;
      default:
        cout << "Invalid option. Please try again.\n";
    }
    press_enter_to_continue();
  } while(true);
}
