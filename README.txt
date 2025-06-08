C++ 圖片處理系統說明文件
======================

本專案是一個用 C++ 實作的互動式圖片處理系統，
支援彩色與灰階圖片載入、資料夾批次處理、
圖片加密與資訊隱藏功能。透過選單操作，
使用者可輕鬆進行各種圖片處理與儲存。

----------------------
【編譯方式】
----------------------
# 預設編譯
$ make

# 顯示詳細編譯過程（除錯用）
$ make VERBOSE=1

# 使用多核心平行編譯（推薦，加速編譯時間）
$ make -j

----------------------
【執行方式】
----------------------
# 執行主程式
$ ./Image_Processing

----------------------
【記憶體檢查方式】
----------------------
# 動態記憶體檢查（需關閉圖片視窗顯示 X Server）
$ make check

----------------------
【使用注意事項】
----------------------
1. 所有選單操作皆為「單選模式」，一次只能選一個選項執行。
2. 執行過程中遇到「press_enter_to_continue」時，
   有時需連按兩次 Enter 才能繼續。
3. 展示圖片時，需「手動關閉視窗」後程式才會繼續執行。
4. main_function 資料夾中儲存各種主選單驅動程式（driven code）。
5. 圖片加密模組被拆成兩組檔案：
   - image_cryptography.h/.cpp：負責傳統加密（XOR、Caesar 等）
   - image_steganography.h/.cpp：負責資訊隱藏（LSB 編碼等）
6. 按下「Save and Return」後，
   所有列表上的圖片將會儲存至「Processed_Image-Folder」資料夾，
   並清除當前已載入的圖片。

----------------------
【專案架構】
----------------------
.
├── Data-Loader
│?? ├── data_loader.cpp
│?? └── data_loader.h
├── data_loader_demo.cpp
├── Data_Loader_Example
├── Image-Folder
│?? ├── 1-1.jpg
│?? ├── 1-2.jpg
│?? ├── 2-1.jpg
│?? ├── 2-2.jpg
│?? ├── 3-1.jpg
│?? ├── 3-2.jpg
│?? ├── 4-1.jpg
│?? ├── 4-2.jpg
│?? ├── lena.jpg
│?? └── truck.png
├── Image_Processing
├── inc
│?? ├── bit_field_filter.h
│?? ├── gray_image.h
│?? ├── image_cryptography.h
│?? ├── image.h
│?? ├── image_steganography.h
│?? └── rgb_image.h
├── LICENSE
├── main.cpp
├── main_function
│?? ├── command_mode.cpp
│?? ├── cryptography_menu.cpp
│?? ├── filter_menu.cpp
│?? ├── image_analysis.cpp
│?? ├── image_loader.cpp
│?? ├── main_function.h
│?? ├── menu_util.cpp
│?? ├── save_and_return.cpp
│?? └── steganography_menu.cpp
├── Makefile
├── obj
│?? ├── bit_field_filter.d
│?? ├── bit_field_filter.o
│?? ├── command_mode.d
│?? ├── command_mode.o
│?? ├── cryptography_menu.d
│?? ├── cryptography_menu.o
│?? ├── data_loader.d
│?? ├── data_loader.o
│?? ├── filter_menu.d
│?? ├── filter_menu.o
│?? ├── gray_image.d
│?? ├── gray_image.o
│?? ├── image_analysis.d
│?? ├── image_analysis.o
│?? ├── image_cryptography.d
│?? ├── image_cryptography.o
│?? ├── image.d
│?? ├── image_loader.d
│?? ├── image_loader.o
│?? ├── image.o
│?? ├── image_steganography.d
│?? ├── image_steganography.o
│?? ├── menu_util.d
│?? ├── menu_util.o
│?? ├── rgb_image.d
│?? ├── rgb_image.o
│?? ├── save_and_return.d
│?? ├── save_and_return.o
│?? ├── steganography_menu.d
│?? └── steganography_menu.o
├── Processed_Image-Folder
├── README.md
├── README.txt
├── Report 113511007.pdf
├── scripts
│?? └── clone_env.sh
├── src
│?? ├── bit_field_filter.cpp
│?? ├── gray_image.cpp
│?? ├── image.cpp
│?? ├── image_cryptography.cpp
│?? ├── image_steganography.cpp
│?? └── rgb_image.cpp
└── third-party
    ├── catimg
    ├── CImg
    └── libjpeg