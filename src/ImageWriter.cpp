#include "ImageWriter.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>

bool ImageWriter::savePPM(const std::string& filename, int width, int height, 
                         const std::vector<Color>& pixels) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return false;
    }
    
    // PPM header
    file << "P3\n";
    file << width << " " << height << "\n";
    file << "255\n";
    
    // Pixel data
    for (int y = height - 1; y >= 0; --y) { // PPM format is top-to-bottom
        for (int x = 0; x < width; ++x) {
            const Color& pixel = pixels[y * width + x];
            
            // Gamma correction and clamping
            Color corrected = pixel.clamped().gammaCorrected(2.2f);
            
            unsigned char r, g, b;
            clampAndConvert(corrected, r, g, b);
            
            file << static_cast<int>(r) << " " 
                 << static_cast<int>(g) << " " 
                 << static_cast<int>(b) << "\n";
        }
    }
    
    file.close();
    std::cout << "Image saved to " << filename << std::endl;
    return true;
}

bool ImageWriter::saveRaw(const std::string& filename, int width, int height, 
                         const std::vector<unsigned char>& data) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing" << std::endl;
        return false;
    }
    
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
    
    std::cout << "Raw image data saved to " << filename << std::endl;
    return true;
}

void ImageWriter::clampAndConvert(const Color& color, unsigned char& r, unsigned char& g, unsigned char& b) {
    r = static_cast<unsigned char>(std::clamp(color.r, 0.0f, 1.0f) * 255.0f);
    g = static_cast<unsigned char>(std::clamp(color.g, 0.0f, 1.0f) * 255.0f);
    b = static_cast<unsigned char>(std::clamp(color.b, 0.0f, 1.0f) * 255.0f);
}
