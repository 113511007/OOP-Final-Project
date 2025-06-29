#ifndef MAIN_FUNCTION_H
#define MAIN_FUNCTION_H

#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include "image.h"
#include "gray_image.h"
#include "rgb_image.h"

void clear_screen();
void press_enter_to_continue();
void display_title();
void main_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void command_mode_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void load_image_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void image_analysis_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void filter_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void steganography_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names, bool decrypt);
void cryptography_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names, bool decrypt);
void save_and_return(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);
void photo_mosaic_menu(std::vector<Image*>& loaded_images, std::vector<std::string>& image_names);

#endif