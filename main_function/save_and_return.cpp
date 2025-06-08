#include <iostream> 
#include <vector>
#include <string>
#include <cstdio> 
#include <cstdlib>
#include <sys/stat.h>
#include <dirent.h> 
#include "image.h" 
#include "main_function.h"

#ifdef _WIN32
#include <windows.h>
#define PATH_SEPARATOR "\\"
#else
#include <unistd.h>
#define PATH_SEPARATOR "/"
#endif

using namespace std;

void clear_folder(const string& folder) {
  DIR* dir = opendir(folder.c_str());
  if (!dir) return;

  struct dirent* entry;
  while ((entry = readdir(dir)) != nullptr) {
    string name = entry->d_name;
    if (name == "." || name == "..") continue;

    string path = folder + PATH_SEPARATOR + name;
    remove(path.c_str());
  }
  closedir(dir);
}

string get_filename_only(const string& path) {
  size_t pos = path.find_last_of("/\\");
  if (pos == string::npos) return path;
  return path.substr(pos + 1);
}

void save_and_return(vector<Image*>& loaded_images, vector<string>& image_names) {
  const string folder = "Processed_Image-Folder";

  static bool cleared = false;
  if (!cleared) {
    clear_folder(folder);
    cleared = true;
  }

  for (size_t i = 0; i < loaded_images.size(); ++i) {
    string filename = get_filename_only(image_names[i]);
    string filepath = folder + PATH_SEPARATOR + filename;
    loaded_images[i]->DumpImage(filepath);
    cout << "Image saved as: " << filepath << "\n";
  }

  press_enter_to_continue();
}