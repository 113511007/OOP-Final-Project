#include "main_function.h"

int main() {
  vector<Image*> loaded_images;
  vector<string> image_names;
  display_title();
  main_menu(loaded_images, image_names);
  return 0;
}
