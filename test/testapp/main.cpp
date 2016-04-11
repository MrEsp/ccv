#include <iostream>
#include <fstream>


extern "C"
{
  #include "ccv.h"
}

using namespace std;

ccv_swt_param_t &initSWTParams(ccv_swt_param_t &swt_params);
void detectTextOnImage( ccv_dense_matrix_t *image, const ccv_swt_param_t &swt_params, bool printInfo);


int main(int argc, char ** argv) {
    // analyzes input picture and outputs the number of text regions

    ccv_dense_matrix_t* image = 0;
    std::cout << "Input file " << argv[1] << std::endl;
    ccv_read(argv[1], &image, CCV_IO_GRAY | CCV_IO_ANY_FILE);

    ccv_swt_param_t swt_params;
    swt_params = initSWTParams(swt_params);
    bool printInfo = true;


    // ccv_write(image, argv[2], 0, CCV_IO_PNG_FILE, 0);
    detectTextOnImage( image, swt_params, printInfo);
    return 0;
}


void detectTextOnImage( ccv_dense_matrix_t *image, const ccv_swt_param_t &swt_params, bool printInfo) {
    auto * words = ccv_swt_detect_words(image, swt_params);

    if (printInfo)
    {
        std::cout << "Words found: " << words->rnum;

        for (int k = 0; k < words->rnum; k++)
        {
            ccv_rect_t* target = (ccv_rect_t*)ccv_array_get(words, k);
            std::cout << target->x << ";" << target->y << " w=" << target->width << " h=" << target->height << std::endl;
            //std::cout << target->x << ";" << target->y  << std::endl;

        }


    }

}

ccv_swt_param_t &initSWTParams(ccv_swt_param_t &swt_params) {
    swt_params.size = 3;
    swt_params.high_thresh = 200;
    swt_params.low_thresh = 90;


    /* aspect_ratio: The maximum aspect ratio for a letter.
    max_height: The maximum height for a letter.
    min_area: The minimum occupied area for a letter.
    min_height: The minimum height for a letter.
    std_ratio: The inner-class standard derivation when grouping letters.
    */
    swt_params.aspect_ratio = 3;
    swt_params.max_height = 90;
    swt_params.min_height = 7;
    swt_params.min_area = 80;
    swt_params.std_ratio = 0.83;

    /*
     *
     * Grouping parameters

     distance_ratio: The allowable distance variance when grouping letters.
     elongate_ratio: The allowable elongate variance when grouping letters.
     height_ratio: The allowable height variance when grouping letters.
     intensity_thresh: The allowable intensity variance when grouping letters.
     intersect_ratio: The allowable intersect variance when grouping letters.
     letter_thresh: The allowable letter threshold.
     thickness_ratio: The allowable thickness variance when grouping letter
     */
    swt_params.distance_ratio = 3.5;
    swt_params.elongate_ratio = 3.5; // not completely clear what this parameter does, perhaps separate horizontal and vertical disstance
    swt_params.height_ratio = 2;
    swt_params.intensity_thresh = 100; // not that clear what it does
    swt_params.intersect_ratio = 2.4; // not that clear what it does
    swt_params.thickness_ratio = 1.3;
    swt_params.letter_thresh = 4;
    swt_params.letter_occlude_thresh = 2;

    swt_params.breakdown = 0;

    // * parameters below that line had not been initialized before valgrind issue was found
    swt_params.scale_invariant = 1;
    swt_params.interval = 7;
    swt_params.same_word_thresh[0] = 0.000000000000000000001;
    swt_params.same_word_thresh[1] = 0.000000000000000000001;
    swt_params.min_neighbors = 0;

    return swt_params;
}
