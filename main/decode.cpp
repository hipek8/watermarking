
#include "lsb_watermarking.h"

using namespace std;
using namespace cv;
int main(int argc, const char *argv[]) {
    if( argc != 2 )
    {
     cout <<" Usage: decode <picture-file> \n";
     return -1;
    }

    auto image = load_image(argv[1]);
    if (image == nullptr) {
        cout << "Error loading image\n";
        return -1;
    }
    Mat gray_image;
    cvtColor( *image, gray_image, CV_BGR2GRAY);

    Mat decoded = decode(gray_image);
    imwrite("decoded.bmp", decoded);
    cout << "Decoded image written as decoded.bmp\n";

    
}
