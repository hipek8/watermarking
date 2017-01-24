#include "WatermarkDecoder.h"

using namespace std;
using namespace cv;

WatermarkDecoder::WatermarkDecoder(const char* filename) {
    _image = load_image(filename);
    if (_image == nullptr) {
        cout << "Error when loading image\nExitting...\n";
        throw 15;
    }
        
}

void WatermarkDecoder::decode(const char* dest_file) {
    Mat decoded = Mat::zeros(_image->rows, _image->cols,CV_8UC(1));
    for (int y=0; y< _image->rows; y++) {
        for (int x=0; x< _image->cols; x++) {
            // amplify least significant bit of first channel
            decoded.at<uchar>(y,x) = 255 * (_image->at<Vec3b>(y,x).val[0] & 1); 
            
        }
    }

    imwrite(dest_file, decoded);
    
}
