#include <fstream>
#include "image_cryptography.h"
#include "main_function.h"
using namespace std;

vector<int> createInverseTable(const vector<int>& table) {
  vector<int> inverse(256);
  for (int i = 0; i < 256; ++i) {
    inverse[table[i]] = i;
  }
  return inverse;
}

string build_processed_filename(const string& original, const string& prefix, bool is_decrypted) {
  size_t last_slash = original.find_last_of("/\\");
  string filename = (last_slash == string::npos) ? original : original.substr(last_slash + 1);
  return prefix + (is_decrypted ? "decrypted_" : "encrypted_") + filename;
}

void cryptography_menu(vector<Image*>& loaded_images, vector<string>& image_names, bool decrypt) {
  string xor_key = "";
  int caesar_shift = 0;
  vector<int> default_table(256), substitution_table(256), dummy;

  for (int i = 0; i < 256; ++i) default_table[i] = (i + 50) % 256;
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

  int choice;
  bool finish = false;
  
  do {
    display_title();
    cout << "=================================\n";
    cout << "Cryptography Menu\n";
    cout << "Image: " << image_names[img_choice - 1] << "\n";
    cout << "=================================\n";
    cout << "1. XOR " << (decrypt ? "De" : "En") << "cryption\n";
    cout << "2. Caesar Cipher " << (decrypt ? "De" : "En") << "cryption\n";
    cout << "3. Substitution Cipher " << (decrypt ? "De" : "En") << "cryption\n";
    cout << "4. Return\n";
    cout << "Enter option: ";
    cin >> choice;

    Image* img = loaded_images[img_choice-1];
    if (img->get_channels() == 1) img = new GrayImage (loaded_images[img_choice-1]->get_width(), loaded_images[img_choice-1]->get_height(), loaded_images[img_choice-1]->gray_get_pixels());
    else img = new RGBImage (loaded_images[img_choice-1]->get_width(), loaded_images[img_choice-1]->get_height(), loaded_images[img_choice-1]->rgb_get_pixels());

    string input;
    switch (choice) {
      case 1: {
        cout << "Enter XOR key (or 'd' for default 'secret_key'): ";
        cin >> input;
        xor_key = (input == "d") ? "secret_key" : input;
        applyEncryption(img, USE_XOR, xor_key, 0, dummy);
        cout << "XOR " << (decrypt ? "de" : "en") << "cryption applied!\n";
        string original_path = image_names[img_choice - 1];
        size_t last_slash = original_path.find_last_of("/\\");
        string original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        string new_filename = string("XOR_") + (decrypt ? "decrypted_" : "encrypted_") + original_filename;
        new_filename = new_filename.substr(0, new_filename.find_last_of(".")) + ".png";
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        img->Display_X_Server();
        press_enter_to_continue();
        finish = true;
        break;
      }
      case 2: {
        cout << "Enter Caesar shift value (or 'd' for default 5): ";
        cin >> input;
        caesar_shift = (input == "d") ? 5 : stoi(input);
        applyEncryption(img, USE_CAESAR, "", (decrypt ? -caesar_shift : caesar_shift), dummy);
        cout << "Caesar cipher " << (decrypt ? "de" : "en") << "cryption applied!\n";
        string original_path = image_names[img_choice - 1];
        size_t last_slash = original_path.find_last_of("/\\");
        string original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        string new_filename = string("Caesar_Cipher_") + (decrypt ? "decrypted_" : "encrypted_") + original_filename;
        new_filename = new_filename.substr(0, new_filename.find_last_of(".")) + ".png";
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        img->Display_X_Server();
        press_enter_to_continue();
        finish = true;
        break;
      }
      case 3: {
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
        applyEncryption(img, USE_SUBSTITUTION, "", 0, (decrypt ? createInverseTable(substitution_table) : substitution_table));
        cout << "Substitution cipher " << (decrypt ? "de" : "en") << "cryption applied!\n";
        string original_path = image_names[img_choice - 1];
        size_t last_slash = original_path.find_last_of("/\\");
        string original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        string new_filename = string("Substitution_Cipher_") + (decrypt ? "decrypted_" : "encrypted_") + original_filename;
        new_filename = new_filename.substr(0, new_filename.find_last_of(".")) + ".png";
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        img->Display_X_Server();
        press_enter_to_continue();
        finish = true;
        break;
      }
      case 4:
        return;
      default:
        cout << "Invalid option.\n";
        press_enter_to_continue();
    }
  } 
  while (!finish);
}