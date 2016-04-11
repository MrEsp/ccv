It was noticed that swt algorithm corrupts the memory and doing some improper memory usage:

Reproduction steps:

1) compile testapp project (CMake is avaliable, see OPTIMIZED_BUILD variable, default is TRUE - meaning O3 compiler option)
2) Run:
	./testapp ../TestData/street2.png
   See that some result is produced
3) Run under valgrind:
   
   valgrind ./testapp ../TestData/street2.png
   valgrind --undef-value-errors=no ./testapp ../TestData/street2.png


Some example of an error valgrind shows


==6025== Invalid write of size 4
==6025==    at 0x5C2E09: ccv_canny (in /home/xxx/src/repo/libccv_fork/ccv/test/testapp/Debug/testapp)
==6025==    by 0x40835E: ccv_swt (in /home/xxx/src/repo/libccv_fork/ccv/test/testapp/Debug/testapp)
==6025==    by 0x4399CF: ccv_swt_detect_words (in /home/xxx/src/repo/libccv_fork/ccv/test/testapp/Debug/testapp)
==6025==    by 0x4032E6: detectTextOnImage(ccv_dense_matrix_t*, ccv_swt_param_t const&, bool) (main.cpp:35)
==6025==    by 0x403296: main (main.cpp:29)
==6025==  Address 0x69cc790 is 560 bytes inside an unallocated block of size 162,768 in arena "client"
