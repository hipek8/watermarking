#include "lsb_watermarking.h"

class WatermarkEncoder {
public:
    WatermarkEncoder (const char*);
    virtual ~WatermarkEncoder () {};
    bool encode(std::vector<int>, const char*);

private:
    const std::map<int, std::vector<std::vector<int>>> _bitmap = {
        { 0 , {{1,1,0},{1,0,1},{1,0,1},{1,0,1},{0,1,1}}},
        { 1 , {{0,1,0},{1,1,0},{0,1,0},{0,1,0},{0,1,0}}},
        { 2 , {{1,1,0},{0,0,1},{0,1,1},{1,0,0},{1,1,1}}},
        { 3 , {{1,1,1},{0,0,1},{0,1,0},{0,0,1},{1,1,1}}},
        { 4 , {{1,0,1},{1,0,1},{1,1,1},{0,0,1},{0,0,1}}},
        { 5 , {{1,1,1},{1,0,0},{1,1,0},{0,0,1},{1,1,0}}},
        { 6 , {{0,1,1},{1,0,0},{1,1,1},{1,0,1},{0,1,1}}},
        { 7 , {{1,1,1},{0,0,1},{0,1,0},{1,0,0},{1,0,0}}},
        { 8 , {{1,1,1},{1,0,1},{1,1,1},{1,0,1},{1,1,1}}},
        { 9 , {{0,1,1},{1,0,1},{1,1,1},{0,0,1},{1,1,0}}}
        };

    const int _x_num = 3;
    const int _x_gap = _x_num + 1;
    const int _y_num = 5;
    const int _y_gap = _y_num + 1;

    int _numbers_per_row;
    int _max_rows;
    int _max_numbers;

    cv::Mat _gray_image;

    // hides given number on least significant bits of given image block
    void hide_single_number(cv::Mat&, int);

    // hides all numbers in gray image
    bool hide_numbers(std::vector<int>);

    // returns start position (x,y) of nth number,
    // (-1, -1) if it cannot fit
    std::pair<int, int> xy_of_nth_block(int);

    cv::Mat load_nth_block(int);

    // puts given block into original image
    void substitute_block(cv::Mat&, int, int);

    
};
