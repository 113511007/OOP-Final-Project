C++ �Ϥ��B�z�t�λ������
======================

���M�׬O�@�ӥ� C++ ��@�����ʦ��Ϥ��B�z�t�ΡA
�䴩�m��P�Ƕ��Ϥ����J�B��Ƨ��妸�B�z�B
�Ϥ��[�K�P��T���å\��C�z�L���ާ@�A
�ϥΪ̥i���P�i��U�عϤ��B�z�P�x�s�C

----------------------
�i�sĶ�覡�j
----------------------
# �w�]�sĶ
$ make

# ��ܸԲӽsĶ�L�{�]�����Ρ^
$ make VERBOSE=1

# �ϥΦh�֤ߥ���sĶ�]���ˡA�[�t�sĶ�ɶ��^
$ make -j

----------------------
�i����覡�j
----------------------
# ����D�{��
$ ./Image_Processing

----------------------
�i�O�����ˬd�覡�j
----------------------
# �ʺA�O�����ˬd�]�������Ϥ�������� X Server�^
$ make check

----------------------
�i�ϥΪ`�N�ƶ��j
----------------------
1. �Ҧ����ާ@�Ҭ��u���Ҧ��v�A�@���u���@�ӿﶵ����C
2. ����L�{���J��upress_enter_to_continue�v�ɡA
   ���ɻݳs���⦸ Enter �~���~��C
3. �i�ܹϤ��ɡA�ݡu������������v��{���~�|�~�����C
4. main_function ��Ƨ����x�s�U�إD����X�ʵ{���]driven code�^�C
5. �Ϥ��[�K�ҲճQ�����ɮסG
   - image_cryptography.h/.cpp�G�t�d�ǲΥ[�K�]XOR�BCaesar ���^
   - image_steganography.h/.cpp�G�t�d��T���á]LSB �s�X���^
6. ���U�uSave and Return�v��A
   �Ҧ��C��W���Ϥ��N�|�x�s�ܡuProcessed_Image-Folder�v��Ƨ��A
   �òM����e�w���J���Ϥ��C

----------------------
�i�M�׬[�c�j
----------------------
.
�u�w�w Data-Loader
�x?? �u�w�w data_loader.cpp
�x?? �|�w�w data_loader.h
�u�w�w data_loader_demo.cpp
�u�w�w Data_Loader_Example
�u�w�w Image-Folder
�x?? �u�w�w 1-1.jpg
�x?? �u�w�w 1-2.jpg
�x?? �u�w�w 2-1.jpg
�x?? �u�w�w 2-2.jpg
�x?? �u�w�w 3-1.jpg
�x?? �u�w�w 3-2.jpg
�x?? �u�w�w 4-1.jpg
�x?? �u�w�w 4-2.jpg
�x?? �u�w�w lena.jpg
�x?? �|�w�w truck.png
�u�w�w Image_Processing
�u�w�w inc
�x?? �u�w�w bit_field_filter.h
�x?? �u�w�w gray_image.h
�x?? �u�w�w image_cryptography.h
�x?? �u�w�w image.h
�x?? �u�w�w image_steganography.h
�x?? �|�w�w rgb_image.h
�u�w�w LICENSE
�u�w�w main.cpp
�u�w�w main_function
�x?? �u�w�w command_mode.cpp
�x?? �u�w�w cryptography_menu.cpp
�x?? �u�w�w filter_menu.cpp
�x?? �u�w�w image_analysis.cpp
�x?? �u�w�w image_loader.cpp
�x?? �u�w�w main_function.h
�x?? �u�w�w menu_util.cpp
�x?? �u�w�w save_and_return.cpp
�x?? �|�w�w steganography_menu.cpp
�u�w�w Makefile
�u�w�w obj
�x?? �u�w�w bit_field_filter.d
�x?? �u�w�w bit_field_filter.o
�x?? �u�w�w command_mode.d
�x?? �u�w�w command_mode.o
�x?? �u�w�w cryptography_menu.d
�x?? �u�w�w cryptography_menu.o
�x?? �u�w�w data_loader.d
�x?? �u�w�w data_loader.o
�x?? �u�w�w filter_menu.d
�x?? �u�w�w filter_menu.o
�x?? �u�w�w gray_image.d
�x?? �u�w�w gray_image.o
�x?? �u�w�w image_analysis.d
�x?? �u�w�w image_analysis.o
�x?? �u�w�w image_cryptography.d
�x?? �u�w�w image_cryptography.o
�x?? �u�w�w image.d
�x?? �u�w�w image_loader.d
�x?? �u�w�w image_loader.o
�x?? �u�w�w image.o
�x?? �u�w�w image_steganography.d
�x?? �u�w�w image_steganography.o
�x?? �u�w�w menu_util.d
�x?? �u�w�w menu_util.o
�x?? �u�w�w rgb_image.d
�x?? �u�w�w rgb_image.o
�x?? �u�w�w save_and_return.d
�x?? �u�w�w save_and_return.o
�x?? �u�w�w steganography_menu.d
�x?? �|�w�w steganography_menu.o
�u�w�w Processed_Image-Folder
�u�w�w README.md
�u�w�w README.txt
�u�w�w Report 113511007.pdf
�u�w�w scripts
�x?? �|�w�w clone_env.sh
�u�w�w src
�x?? �u�w�w bit_field_filter.cpp
�x?? �u�w�w gray_image.cpp
�x?? �u�w�w image.cpp
�x?? �u�w�w image_cryptography.cpp
�x?? �u�w�w image_steganography.cpp
�x?? �|�w�w rgb_image.cpp
�|�w�w third-party
    �u�w�w catimg
    �u�w�w CImg
    �|�w�w libjpeg