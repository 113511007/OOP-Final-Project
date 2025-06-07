#include "bit_field_filter.h"
#include "main_function.h"
using namespace std;

void filter_menu(vector<Image*>& loaded_images, vector<string>& image_names) {
  if (loaded_images.empty()) return;

  static uint8_t filter_options = 0;
  static int mosaic_block_size = 5;
  static int gaussian_sd = 1;
  static int luminance_scale = 20;

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

  Image* img = loaded_images[img_choice-1];
  
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
    if (filter_options & FILTER_COLD) cout << "Cold ";
    if (filter_options & FILTER_WARM) cout << "Warm ";
    if (filter_options & FILTER_LUMINANCE) cout << "Luminance(" << luminance_scale << "%) ";
    cout << "\n=================================\n";
    cout << "1. Horizontal Flip\n";
    cout << "2. Mosaic (Block size: " << mosaic_block_size << ")\n";
    cout << "3. Gaussian Blur (SD: " << gaussian_sd << ")\n";
    cout << "4. Laplacian Sharpen\n";
    cout << "5. Fisheye Effect\n";
    cout << "6. Cold Adjustment\n";
    cout << "7. Warm Adjustment\n";
    cout << "8. Luminance Enhancement (" << luminance_scale << "%)\n";
    cout << "9. Set Filter Parameters\n";
    cout << "10. Preview Effects\n";
    cout << "11. Load the Filtered Image\n";
    cout << "12. Clear all filters\n";
    cout << "13. Return to Previous Menu\n";
    cout << "Enter an option (1–12): ";
    cin >> choice;

    Image* filtered_img;

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
        cout << "Set which parameter?\n";
        cout << "  1. Mosaic block size\n";
        cout << "  2. Gaussian blur SD\n";
        cout << "  3. Luminance scale (%)\n";
        cout << "Enter your choice (1–3): ";
        cin >> param_choice;
        switch (param_choice) {
          case 1:
            cout << "Enter new mosaic block size: ";
            cin >> mosaic_block_size;
            break;
          case 2:
            cout << "Enter new Gaussian blur SD: ";
            cin >> gaussian_sd;
            break;
          case 3:
            cout << "Enter new luminance scale (%): ";
            cin >> luminance_scale;
            break;
          default:
            cout << "Invalid parameter selection.\n";
        }
        break;
      }
      case 10: {
        applyFilters(*img, filter_options, mosaic_block_size, gaussian_sd, luminance_scale);
        img->Display_X_Server();
        press_enter_to_continue();
        img->LoadImage(image_names[img_choice-1]);
        break;
      }
      case 11: {
        if (img->get_channels() == 1) filtered_img = new GrayImage (img->get_width(), img->get_height(), img->gray_get_pixels());
        else filtered_img = new RGBImage (img->get_width(), img->get_height(), img->rgb_get_pixels());
        loaded_images.push_back(filtered_img);
        image_names.push_back("filtered_" + image_names[img_choice - 1]);
        img->Display_X_Server();
        img->LoadImage(image_names[img_choice-1]);
        press_enter_to_continue();
        break;        
      }
      case 12:
        filter_options = 0;
        break;
      case 13:
        return;
      default:
        cout << "Invalid option. Please try again.\n";
        press_enter_to_continue();
    }
  } while (true);
}
