#include <iostream>
#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>
#include <map>
#include <vector>
#include <bitset>
#include <unistd.h>

const std::map<int, std::vector<std::vector<int>>> bitmap = {
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

static const int x_num= 3;
static const int x_gap = x_num + 1;
static const int y_num = 5;
static const int y_gap = y_num + 1;

std::unique_ptr<cv::Mat> load_image(const char *);
std::unique_ptr<cv::Mat> load_gray(const char *);

void hide_single_number(cv::Mat&, int);

bool hide_numbers(cv::Mat&, std::vector<int>);

cv::Mat decode(cv::Mat&);
