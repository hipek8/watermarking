#include "lsb_watermarking.h"

class WatermarkDecoder {
public:
    WatermarkDecoder (const char*);
    virtual ~WatermarkDecoder () {};

    void decode(const char*);

private:
    
    std::unique_ptr<cv::Mat> _image;
};
