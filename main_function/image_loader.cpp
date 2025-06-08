#include "main_function.h"
#include "data_loader.h"
#include <sys/stat.h> 
#include <algorithm>
using namespace std;

bool is_directory(const string& path) {
    struct stat info;
    if (stat(path.c_str(), &info) != 0) return false;
    return (info.st_mode & S_IFDIR);
}

void load_image_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
    Data_Loader loader;
    string path;
    int mode_choice = 0;

    do {
        display_title();
        cout << "=================================\n";
        if (loaded_images.empty()) {
            cout << "No images loaded.\n";
        } else {
            cout << "Current loaded images:\n";
            for (size_t i = 0; i < loaded_images.size(); ++i) {
                cout << i + 1 << ". " << image_names[i] << " ("
                     << loaded_images[i]->get_width() << "x"
                     << loaded_images[i]->get_height() << " "
                     << (loaded_images[i]->get_channels() == 1 ? "Grayscale" : "RGB")
                     << ")\n";
            }
        }
        cout << "=================================\n";

        cout << "Choose loading type:\n";
        cout << "1. Load single image\n";
        cout << "2. Load all images from a folder\n";
        cout << "Enter your choice (1-2, or 0 to go back): ";
        cin >> mode_choice;
        if (mode_choice == 0) return;

        cin.ignore();
        cout << (mode_choice == 1 ? "Enter image file path: " : "Enter folder path: ");
        getline(cin, path);

        int load_mode = 0;
        cout << "Select image loading mode:\n";
        cout << "1. Load as RGB\n";
        cout << "2. Load as Grayscale\n";
        cout << "3. Auto Detect (try RGB then Grayscale)\n";
        cout << "Enter your choice (1-3): ";
        cin >> load_mode;

        auto load_image = [&](const string& file_path, const string& display_name) {
            string ext = file_path.substr(file_path.find_last_of(".") + 1);
            transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
            if (ext != "jpg" && ext != "png") return;

            Image* new_image = nullptr;
            bool loaded = false;

            if (load_mode == 1) {
                new_image = new RGBImage();
                loaded = new_image->LoadImage(file_path);
            } else if (load_mode == 2) {
                new_image = new GrayImage();
                loaded = new_image->LoadImage(file_path);
            } else if (load_mode == 3) {
                new_image = new RGBImage();
                if (!(loaded = new_image->LoadImage(file_path))) {
                    delete new_image;
                    new_image = new GrayImage();
                    loaded = new_image->LoadImage(file_path);
                }
            }

            if (loaded) {
                loaded_images.push_back(new_image);
                image_names.push_back(display_name);
                cout << "Image '" << display_name << "' loaded successfully as "
                     << (new_image->get_channels() == 1 ? "Grayscale" : "RGB") << "!\n";
            } else {
                delete new_image;
                cout << "Failed to load image: " << display_name << "\n";
            }
        };

        if (mode_choice == 1) {
            load_image(path, path); 
        } else if (mode_choice == 2) {
            if (!is_directory(path)) {
                cout << "Error: Path is not a folder.\n";
            } else {
                vector<string> file_list;
                bool success = (loader.List_Directory(path, file_list) == 0);
                if (success && !file_list.empty()) {
                    for (const string& filename : file_list) {
                        string full_path = path + "/" + filename;
                        load_image(full_path, filename);
                    }
                } else {
                    cout << "Folder is empty or unreadable.\n";
                }
            }
        } else {
            cout << "Invalid mode selection.\n";
        }

        press_enter_to_continue();
    } while (true);
}