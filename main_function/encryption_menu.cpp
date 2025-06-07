#include <fstream>
#include "image_encryption.h"
#include "main_function.h"
using namespace std;

vector<int> createDefaultTable() {
  vector<int> table(256);
  for (int i = 0; i < 256; ++i) {
    table[i] = (i + 50) % 256;
  }
  return table;
}

vector<int> createInverseTable(const vector<int>& table) {
  vector<int> inverse(256);
  for (int i = 0; i < 256; ++i) {
    inverse[table[i]] = i;
  }
  return inverse;
}

void encryption_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  if (loaded_images.empty()) return;

  string lsb_message = "";
  string xor_key = "";
  int caesar_shift = 0;
  bool substitution_encryption = false;
  vector<int> x, default_table, substitution_table;
  default_table = createDefaultTable();
  substitution_table = default_table;
  
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
    cout << "Image Encryption: " << image_names[img_choice-1] << "\n";
    cout << "=================================\n";
    cout << "Current settings:\n";
    cout << "1. LSB Steganography - Message: " << ((lsb_message.empty() || lsb_message == "Hello World") ? "[Default]" : "[Set]") << "\n";
    cout << "2. XOR Encryption - Key: " << ((xor_key.empty() || xor_key == "secret_key") ? "[Default]" : "[Set]") << "\n";
    cout << "3. Caesar Cipher - Shift: " << caesar_shift << "\n";
    cout << "4. Substitution Table - " << (substitution_table == default_table ? "[Default]" : "[Set]") << "\n";
    cout << "5. Decrypt Current Image\n";
    cout << "6. Preview Encrypted Image\n";
    cout << "7. Back to Default Mode\n";
    cout << "8. Return to Previous Menu\n";
    cout << "Enter option: ";
    cin >> choice;
    
    Image* encrypted_img;
    
    switch(choice) {
      case 1: {
        cout << "Enter message for LSB steganography (or 'd' for default 'Hello World'): ";
        cin.ignore();
        getline(cin, lsb_message);
        if (lsb_message == "d") {
          lsb_message = "Hello World";
        }
        applyEncryption(img, ENCRYPT_LSB, lsb_message, "", 0, x);
        cout << "Message embedded successfully!\n";
        press_enter_to_continue();
        break;
      }
      case 2: {
        cout << "Enter XOR key (or 'd' for default 'secret_key'): ";
        string input;
        cin >> input;
        xor_key = (input == "d") ? "secret_key" : input;
        applyEncryption(img, ENCRYPT_XOR, "", xor_key, 0, x);
        cout << "XOR encryption applied!\n";
        press_enter_to_continue();
        break;
      }
      case 3: {
        cout << "Enter Caesar shift value (or 'd' for default 5): ";
        string input;
        cin >> input;
        caesar_shift = (input == "d") ? 5 : stoi(input);
        applyEncryption(img, ENCRYPT_CAESAR, "", "", caesar_shift, x);
        cout << "Caesar cipher applied with shift " << caesar_shift << "!\n";
        press_enter_to_continue();
        break;
      }
      case 4: {
        substitution_encryption = true;
        cout << "Choose substitution table source:\n";
        cout << "1. Use default table\n";
        cout << "2. Load from file\n";
        cout << "3. Enter manually\n";
        cout << "Option: ";
        int table_choice;
        cin >> table_choice;
        if (table_choice == 1) {
          cout << "Using default substitution table.\n";
          substitution_table = default_table;
        } 
        else if (table_choice == 2) {
          cout << "Enter filename containing substitution table: ";
          string filename;
          cin >> filename;
          ifstream file(filename);
          if (file.is_open()) {
            for (int i = 0; i < 256; ++i) {
              if (!(file >> substitution_table[i])) {
                cout << "Error reading table from file. Using default.\n";
                substitution_table = default_table;
                break;
              }
            }
            cout << "Substitution table loaded from file.\n";
            file.close();
          } 
          else {
            cout << "Failed to open file. Using default table.\n";
            substitution_table = default_table;
          }
        }
        else if (table_choice == 3) {
          cout << "Enter 256 space-separated values (0-255):\n";
          for (int i = 0; i < 256; ++i) {
            cin >> substitution_table[i];
          }
          cout << "Substitution table entered manually.\n";
        }
        else {
          cout << "Invalid choice. Using default table.\n";
        }
        applyEncryption(img, ENCRYPT_SUBSTITUTION, "", "", 0, substitution_table);
        cout << "Substitution cipher applied!\n";
        press_enter_to_continue();
        break;
      }
      case 5: {
        cout << "Decrypting image...\n";
        applyEncryption(img, DECRYPT_LSB, "", "", 0, x);
        if (!xor_key.empty()) {
          applyEncryption(img, ENCRYPT_XOR, "", xor_key, 0, x);
        }
        if (caesar_shift != 0) {
          applyEncryption(img, ENCRYPT_CAESAR, "", "", -caesar_shift, x);
        }
        if (substitution_encryption == true) {
          vector<int> inverse_table = createInverseTable(substitution_table);
          applyEncryption(img, ENCRYPT_SUBSTITUTION, "", "", 0, inverse_table);
        }
        cout << "Decryption completed!\n";
        press_enter_to_continue();
        break;
      }
      case 6:
        if (img->get_channels() == 1) encrypted_img = new GrayImage (img->get_width(), img->get_height(), img->gray_get_pixels());
        else encrypted_img = new RGBImage (img->get_width(), img->get_height(), img->rgb_get_pixels());
        loaded_images.push_back(encrypted_img);
        image_names.push_back("encrypted_" + image_names[img_choice - 1].substr(0, image_names[img_choice - 1].find_last_of('.')) + ".png");
        img->Display_X_Server();
        img->LoadImage(image_names[img_choice-1]);
        press_enter_to_continue();
        break;
      case 7:
        lsb_message = "";
        xor_key = "";
        caesar_shift = 0;
        substitution_encryption = false;
        break;
      case 8:
        return;
      default:
        cout << "Invalid option. Please try again.\n";
        press_enter_to_continue();
    }
  } 
  while(true);
}
