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
שÝשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששß
שר        *  IMAGE PROCESSING LAB  *         שר
שר                                           שר
שר       ¢i??????????????????????????¢i        שר
שר       ¢i  2025 OOP FINAL PROJECT  ¢i        שר
שר       ????????????????????????????        שר
שר                113511007                  שר
שדשששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששששו
)" << endl;
}
