1.編譯方式與預設相同：

# compile
$ make               # default
$ make VERBOSE=1     # check out what make actually do
$ make -j            # compile in parallel (save time, suggest)

2.執行方式與預設相同：
# run your program
$ ./Image_Processing

3.記憶體檢查方式與預設相同：
# Dynamic memory check (Need to disable the Display_X_Server...)
$ make check

4.執行時每個case選擇都是單選

5.遇到press_enter_to_continue有時按一次enter會卡住，須按兩次enter

6.X_server展示圖片後，要關掉視窗才能進行下一步

7.main_function資料夾儲存各種driven code

8.image_encryption被拆分成兩組檔案：image_cryptography.h/.cpp與image_steganography.h/.cpp

9.執行時，按下save and return後，所有列表上的圖片都會被下載到資料夾Processed_Image-Folder，並清空原有的檔案