#include "lsb_watermarking.h"

using namespace std;
using namespace cv;

unique_ptr<Mat> load_some(const char *name, int flags) {
    auto image = make_unique<Mat>(imread(name, flags));   // Read the file
    if( !image->data )                                    // Check for invalid input
    {
        return nullptr;
    }
    return image;
}

unique_ptr<Mat> load_gray(const char *name) {
    return load_some(name, 0);
};
unique_ptr<Mat> load_image(const char *name) {
    return load_some(name, CV_LOAD_IMAGE_COLOR);
};

void hide_single_number(Mat& block, int number) {
    Mat new_block = Mat::zeros(block.rows, block.cols,CV_8UC(1));
    for (int y=0; y<block.rows; y++) {
        for (int x=0; x<block.cols; x++) {
            bool lsb;
            try {
                lsb = bitmap.at(number).at(y).at(x);
            } catch (...) {
                lsb = 0;
            }
            new_block.at<char>(y,x) = (block.at<char>(y,x) & 254) | lsb;
            block.at<char>(y,x) = new_block.at<char>(y,x);
        }
    }
    
}

bool hide_numbers(Mat& image, vector<int> numbers) {
    for (int i=0; i<numbers.size(); i++) {
        Mat block = Mat::zeros(y_gap, x_gap, CV_8UC(1));
        for (int y = 0; y < y_gap; y++) {
            for (int x = 0; x < x_gap; x++) {
                int x_src = x_gap * i + x;
                int y_src = y;
                block.at<char>(y,x) = image.at<char>(y_src, x_src);
            }
        }
        hide_single_number(block, numbers.at(i));
        for (int y = 0; y < y_gap; y++) {
            for (int x = 0; x < x_gap; x++) {
                int x_src = x_gap * i + x;
                int y_src = y;
                image.at<char>(y_src,x_src) = block.at<char>(y, x);
            }
        }
    }
}


Mat decode(Mat& image) {
    Mat decoded = Mat::zeros(image.rows, image.cols,CV_8UC(1));
    for (int y=0; y<image.rows; y++) {
        for (int x=0; x<image.cols; x++) {
            // amplify least significant bit
            decoded.at<char>(y,x) = 255 * (image.at<char>(y,x) & 1); 
        }
    }
    return decoded;
}
