#include "main_function.h"

int main() {
  vector<Image*> loaded_images;
  vector<string> image_names;
  display_title();
  main_menu(loaded_images, image_names);
  for (auto img : loaded_images) {
    delete img;
  }
  loaded_images.clear();
  return 0;
}
