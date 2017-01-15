#include "lsb_watermarking.h"

using namespace std;
using namespace cv;
int main(int argc, const char *argv[]) {
    if( argc != 2 )
    {
     cout <<" Usage: decode <picture-file> \n";
     return -1;
    }

    auto gray_image = load_gray(argv[1]);
    if (gray_image == nullptr) {
        cout << "Error when loading image\nExitting...\n";
        return -1;
    }
    Mat decoded = decode(*gray_image);
    imwrite("decoded.bmp", decoded);
    cout << "Decoded image written as decoded.bmp\n";

    
}
