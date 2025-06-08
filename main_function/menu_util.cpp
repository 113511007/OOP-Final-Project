#include <iostream>
#include <cstdlib>
#include "main_function.h"
using namespace std;

void clear_screen() {
  system("clear");
}

void press_enter_to_continue() {
  cout << "\nPress Enter to continue...";
  cin.ignore();
  cin.get();
}

void display_title() {
  clear_screen();
  cout << R"(
--------------------------------------
|         IMAGE PROCESSING           |
|    -------------o--------------    |
|    OOP Project  |  ID:113511007    |
--------------------------------------
)" << endl;
}
