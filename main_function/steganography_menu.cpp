#include <fstream>
#include "image_steganography.h"
#include "main_function.h"
using namespace std;

void steganography_menu(vector<Image*>& loaded_images, vector<string>& image_names, bool decrypt) { 
  string message; 
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

  int choice;
  bool finish = false;
  
  do { 
    display_title(); 
    cout << "=================================\n"; 
    cout << "Steganography Menu\n"; 
    cout << "Image: " << image_names[img_choice - 1] << "\n";
    cout << "=================================\n"; 
    cout << "1. LSB " << (decrypt ? "De" : "En") << "cryption\n"; 
    cout << "2. Bit-Plane " << (decrypt ? "De" : "En") << "cryption\n"; 
    cout << "3. Return\n"; 
    cout << "Enter option: "; 
    cin >> choice; 
    
    Image* img = loaded_images[img_choice-1];
    if (img->get_channels() == 1) img = new GrayImage (loaded_images[img_choice-1]->get_width(), loaded_images[img_choice-1]->get_height(), loaded_images[img_choice-1]->gray_get_pixels());
    else img = new RGBImage (loaded_images[img_choice-1]->get_width(), loaded_images[img_choice-1]->get_height(), loaded_images[img_choice-1]->rgb_get_pixels());
    
    if (decrypt) { 
      switch (choice) { 
        case 1: 
          cout << "Decrypting image...\n";
          cout << "Embedded message:" << applyDecryption(img, DE_LSB) << "\n"; 
          press_enter_to_continue(); 
          break; 
        case 2: 
          cout << "Decrypting image...\n";
          cout << "Embedded message:" << applyDecryption(img, DE_BITPLANE) << "\n"; 
          press_enter_to_continue(); 
          break; 
        case 3: 
          break; 
        default: 
          cout << "Invalid option.\n"; 
          press_enter_to_continue();
          continue; 
      }
      finish = true;
      continue;
    }
    
    string original_path;
    string original_filename;
    string new_filename;
    size_t last_slash;
    
    switch (choice) { 
      case 1: 
        cout << "Enter message to embed (or 'd' for default - Hello World): "; 
        cin.ignore(); 
        getline(cin, message); 
        if (message == "d") message = "Hello World"; 
        applyEncryption(img, EN_LSB, message); 
        original_path = image_names[img_choice - 1];
        last_slash = original_path.find_last_of("/\\");
        original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        new_filename = "LSB_encrypted_" + original_filename;
        new_filename = new_filename.substr(0, new_filename.find_last_of(".")) + ".png";
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        cout << "Message embedded using LSB!\n"; 
        img->Display_X_Server();
        press_enter_to_continue();
        break; 
      case 2: 
        cout << "Enter message to embed (or 'd' for default - Hello World): ";
        cin.ignore(); 
        getline(cin, message); 
        if (message == "d") message = "Hello World";  
        applyEncryption(img, EN_BITPLANE, message); 
        original_path = image_names[img_choice - 1];
        last_slash = original_path.find_last_of("/\\");
        original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        new_filename = "BitPlane_encrypted_" + original_filename;
        new_filename = new_filename.substr(0, new_filename.find_last_of(".")) + ".png";
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        cout << "Message embedded using Bit-plane!\n"; 
        img->Display_X_Server();
        press_enter_to_continue();
        break; 
      case 3: 
        return; 
      default: 
        cout << "Invalid option.\n"; 
        press_enter_to_continue();
        continue;
    }
    finish = true;
  } 
  while (!finish); 
}
