#include "WatermarkEncoder.h"

using namespace std;
using namespace cv;

WatermarkEncoder::WatermarkEncoder(const char* filename) {
    auto image = load_image(filename);
    if (image == nullptr) {
        cout << "Error when loading image\nExitting...\n";
        throw 15;
    }
    
    _dest_image = *image;
    _numbers_per_row = _dest_image.cols / _x_gap;
    _max_rows = _dest_image.rows / _y_gap;
    _max_numbers = _max_rows * _numbers_per_row;

}

bool WatermarkEncoder::encode(vector<int> numbers, const char* dest_file) {

    hide_numbers(numbers);

    try {
        imwrite(dest_file, _dest_image);
    } catch (runtime_error& ex) {
        return false;
    }
    return true;
}

bool WatermarkEncoder::hide_numbers(vector<int> numbers) {
    for (int i=0; i<numbers.size(); i++) {
        //bound check
        if (i > _max_numbers) {
            return false;
        }

        Mat block = load_nth_block(i);

        hide_single_number(block, numbers.at(i));

        int x,y;
        tie (x,y) = xy_of_nth_block(i);
        substitute_block(block, x, y);

    }
    return true;
}

void WatermarkEncoder::hide_single_number(Mat& block, int number) {
    Mat new_block = Mat::zeros(block.rows, block.cols,CV_8UC(3));
    bool lsb;
    for (int y=0; y<block.rows; y++) {
        for (int x=0; x<block.cols; x++) {
            try {
                lsb = _bitmap.at(number).at(y).at(x);
            } catch (...) {
                lsb = 0;
            }
            Vec3b intensity = block.at<Vec3b>(y,x);
            intensity.val[0] = (intensity.val[0] & 254) | lsb;
            block.at<Vec3b>(y,x) = intensity;
        }
    }
    
}

void WatermarkEncoder::substitute_block(Mat& block, int start_x, int start_y) {

    for (int y = 0; y < _y_gap; y++) {
        for (int x = 0; x < _x_gap; x++) {
            int x_src = start_x + x;
            int y_src = start_y + y;
            _dest_image.at<Vec3b>(y_src,x_src) = block.at<Vec3b>(y, x);
        }
    }

}

Mat WatermarkEncoder::load_nth_block(int n) {
    int start_x, start_y;
    tie(start_x, start_y) = xy_of_nth_block(n);

    Mat block = Mat::zeros(_y_gap, _x_gap, CV_8UC(3));

    for (int y = 0; y < _y_gap; y++) {
        for (int x = 0; x < _x_gap; x++) {
            int x_src = start_x + x;
            int y_src = start_y + y;
            block.at<Vec3b>(y,x) = _dest_image.at<Vec3b>(y_src, x_src);
        }
    }
       
    return block;
}

pair<int, int> WatermarkEncoder::xy_of_nth_block(int n) {
    if ( n > _max_numbers) {
        return pair<int, int>(-1,-1);
    }

    int start_x = _x_gap * (n % _numbers_per_row);
    int start_y = _y_gap * (n / _numbers_per_row);

    return pair<int, int>(start_x, start_y);
};
