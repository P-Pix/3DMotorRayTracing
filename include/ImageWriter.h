#ifndef IMAGE_WRITER_H
#define IMAGE_WRITER_H

#include "Color.h"
#include <vector>
#include <string>

class ImageWriter {
public:
    // Save image as PPM format
    static bool savePPM(const std::string& filename, int width, int height, 
                       const std::vector<Color>& pixels);
    
    // Save image as raw RGB data
    static bool saveRaw(const std::string& filename, int width, int height, 
                       const std::vector<unsigned char>& data);

private:
    static void clampAndConvert(const Color& color, unsigned char& r, unsigned char& g, unsigned char& b);
};

#endif // IMAGE_WRITER_H
