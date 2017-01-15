#include <cv.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <memory>
#include <vector>

std::unique_ptr<cv::Mat> load_image(const char *);
std::unique_ptr<cv::Mat> load_gray(const char *);

cv::Mat decode(cv::Mat&);
