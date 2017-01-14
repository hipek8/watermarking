#include "lsb_watermarking.h"
#include <cstring>
using namespace std;
using namespace cv;

vector<int> parse_numbers(int argc, const char *argv[]) {
    vector<int> numbers;
    for (int i = 2; i < argc; i++) {
        for (int ii = 0; ii<strlen(argv[i]); ii++) {
            int n =  (argv[i][ii]) - '0' ;
            if (n <0 || n> 9) {
                cout << "Ignoring '"<< argv[i][ii]<<"': Only digits allowed\n";
                continue;
            }
            numbers.push_back( n );
        }
    }
    return numbers;
}


int main(int argc, const char *argv[]) {
    if( argc < 2 )
    {
     cout <<" Usage: encode <picture-file> [<digits to hide> ...]" << endl;
     return -1;
    }

    auto image = load_image(argv[1]);
    if (image == nullptr) {
        cout << "Error loading image\n";
        return -1;
    }
    Mat gray_image;
    cvtColor( *image, gray_image, CV_BGR2GRAY);
    vector<int> numbers = parse_numbers(argc, argv);
    hide_numbers(gray_image, numbers);
    Mat gray_3channels;
    cvtColor( gray_image, gray_3channels, CV_GRAY2BGR);
    imwrite("gray.bmp", gray_3channels);
    cout << "Encoded image written as gray.bmp\n";

    return 0;
}
