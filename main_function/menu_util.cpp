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
   _____ _____  ______       _
  / ____|  __ \|  ____|     (_)
 | (___ | |__) | |__   _ __  _  ___ ___
  \___ \|  ___/|  __| | '_ \| |/ __/ __|
 ____) | |    | |____| | | | | | (__\__ \
|_____/|_|    |______|_| | |_|_|\___|___/
)" << endl;
}
