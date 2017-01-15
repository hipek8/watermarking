#include "lsb_watermarking.h"

using namespace std;
using namespace cv;

namespace {
// loads image and returns unique_ptr to its matrix
unique_ptr<Mat> load_some(const char *name, int flags) {
    auto image = make_unique<Mat>(imread(name, flags));   // Read the file
    if( !image->data )                                    // Check for invalid input
    {
        return nullptr;
    }
    return image;
}


}

// loads image with single channel (grayscale)
unique_ptr<Mat> load_gray(const char *name) {
    return load_some(name, 0);
};

// loads image with 3 channels (like RGB)
unique_ptr<Mat> load_image(const char *name) {
    return load_some(name, CV_LOAD_IMAGE_COLOR);
};
