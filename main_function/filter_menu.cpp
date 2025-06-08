#include "bit_field_filter.h"
#include "main_function.h"
using namespace std;

int mosaic_block_size = 5;
int gaussian_sd = 1;
int luminance_scale = 20;
int cold_intensity = 30;
bool cold_preserve_luminance = true;
int warm_intensity = 30;
bool warm_preserve_luminance = true;

void filter_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  if (loaded_images.empty()) return;

  uint8_t filter_options = 0;
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
  do {
    display_title();
    cout << "=================================\n";
    cout << "Filter Processing: " << image_names[img_choice-1] << "\n";
    cout << "Current active filters: ";
    if (filter_options == 0) cout << "None";
    if (filter_options & FILTER_FLIP) cout << "HFlip ";
    if (filter_options & FILTER_MOSAIC) cout << "Mosaic(" << mosaic_block_size << ") ";
    if (filter_options & FILTER_GAUSSIAN) cout << "Gaussian(" << gaussian_sd << ") ";
    if (filter_options & FILTER_LAPLACIAN) cout << "Laplacian ";
    if (filter_options & FILTER_FISHEYE) cout << "Fisheye ";
    if (filter_options & FILTER_COLD) cout << "Cold(" << cold_intensity << "," << (cold_preserve_luminance ? "Lum" : "NoLum") << ") ";
    if (filter_options & FILTER_WARM) cout << "Warm(" << warm_intensity << "," << (warm_preserve_luminance ? "Lum" : "NoLum") << ") ";
    if (filter_options & FILTER_LUMINANCE) cout << "Luminance(" << luminance_scale << "%) ";
    cout << "\n=================================\n";
    cout << "1. Horizontal Flip\n";
    cout << "2. Mosaic (Block size: " << mosaic_block_size << ")\n";
    cout << "3. Gaussian Blur (SD: " << gaussian_sd << ")\n";
    cout << "4. Laplacian Sharpen\n";
    cout << "5. Fisheye Effect\n";
    cout << "6. Cold Adjustment (Intensity: " << cold_intensity << ", Luminance: " << (cold_preserve_luminance ? "Keep" : "Ignore") << ")\n";
    cout << "7. Warm Adjustment (Intensity: " << warm_intensity << ", Luminance: " << (warm_preserve_luminance ? "Keep" : "Ignore") << ")\n";
    cout << "8. Luminance Enhancement (" << luminance_scale << "%)\n";
    cout << "9. Set Filter Parameters\n";
    cout << "10. Preview Effects\n";
    cout << "11. Apply Filters\n";
    cout << "12. Clear all filters\n";
    cout << "13. Return to Previous Menu\n";
    cout << "Enter an option (1–13): ";
    cin >> choice;

    switch (choice) {
      case 1: filter_options ^= FILTER_FLIP; break;
      case 2: filter_options ^= FILTER_MOSAIC; break;
      case 3: filter_options ^= FILTER_GAUSSIAN; break;
      case 4: filter_options ^= FILTER_LAPLACIAN; break;
      case 5: filter_options ^= FILTER_FISHEYE; break;
      case 6: filter_options ^= FILTER_COLD; break;
      case 7: filter_options ^= FILTER_WARM; break;
      case 8: filter_options ^= FILTER_LUMINANCE; break;
      case 9: {
        int param_choice;
        cout << "Set which parameter?\n2. Mosaic Block Size\n3. Gaussian SD\n"
             << "6. Cold Filter\n7. Warm Filter\n8. Luminance Scale\n"
             << "Enter choice (2-3,6-8): ";
        cin >> param_choice;
        switch (param_choice) {
          case 2:
            cout << "Enter mosaic block size (5-20): ";
            cin >> mosaic_block_size;
            break;
          case 3:
            cout << "Enter Gaussian blur SD (1-10): ";
            cin >> gaussian_sd;
            break;
          case 6:
            cout << "Enter cold intensity (0-100): ";
            cin >> cold_intensity;
            cout << "Preserve luminance? (1=Yes/0=No): ";
            cin >> cold_preserve_luminance;
            break;
          case 7:
            cout << "Enter warm intensity (0-100): ";
            cin >> warm_intensity;
            cout << "Preserve luminance? (1=Yes/0=No): ";
            cin >> warm_preserve_luminance;
            break;
          case 8:
            cout << "Enter luminance scale % (0-100): ";
            cin >> luminance_scale;
            break;
          default:
            cout << "Invalid parameter selection.\n";
        }
        press_enter_to_continue();
        break;
      }
      case 10: {
        Image* original = loaded_images[img_choice - 1];
        Image* img = nullptr;
        if (original->get_channels() == 1) {
          img = new GrayImage(original->get_width(), original->get_height(), original->gray_get_pixels());
        } 
        else {
          img = new RGBImage(original->get_width(), original->get_height(), original->rgb_get_pixels());
        }
        applyFilters(*img, filter_options, mosaic_block_size, gaussian_sd, cold_intensity, cold_preserve_luminance, warm_intensity, warm_preserve_luminance, luminance_scale);
        img->Display_X_Server();
        press_enter_to_continue();
        delete img;
        break;
      }
      case 11: {
        Image* original = loaded_images[img_choice - 1];
        Image* img = nullptr;
        if (original->get_channels() == 1) {
          img = new GrayImage(original->get_width(), original->get_height(), original->gray_get_pixels());
        } 
        else {
          img = new RGBImage(original->get_width(), original->get_height(), original->rgb_get_pixels());
        }
        applyFilters(*img, filter_options, mosaic_block_size, gaussian_sd, cold_intensity, cold_preserve_luminance, warm_intensity, warm_preserve_luminance, luminance_scale);
        string original_path = image_names[img_choice - 1];
        string original_filename;
        size_t last_slash = original_path.find_last_of("/\\");
        original_filename = (last_slash == string::npos) ? original_path : original_path.substr(last_slash + 1);
        string new_filename = "filtered_" + original_filename;
        loaded_images.push_back(img);
        image_names.push_back(new_filename);
        cout << "\nFilter applied successfully!\n";
        img->Display_X_Server();
        press_enter_to_continue();
        return;
      }
      case 12:
        filter_options = 0;
        cout << "All filters cleared.\n";
        press_enter_to_continue();
        break;
      case 13:
        return;
      default:
        cout << "Invalid option.\n";
        press_enter_to_continue();
    }
  } while (true);
}
