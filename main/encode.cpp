#include "WatermarkEncoder.h"
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
    if( argc < 3 )
    {
     cout <<" Usage: encode <picture-file> <digits to hide> ..." << endl;
     return -1;
    }
    try {
        auto enc = WatermarkEncoder(argv[1]);
        vector<int> numbers = parse_numbers(argc, argv);

        enc.encode(numbers, "gray.bmp");
        cout << "Encoded image written as gray.bmp\n";

        return 0;
    } catch (...) {
        return -1;
    }
}
