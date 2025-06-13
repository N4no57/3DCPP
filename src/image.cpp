#include "../include/image.hpp"
#include <fstream>

namespace rast {
    void WriteImageToFile(const RenderTarget& image, const std::string& name)
    {
        int width = image.getWidth();
        int height = image.getHeight();

        // Each pixel = 3 bytes, each row must be padded to multiple of 4 bytes
        int rowSize = ((3 * width + 3) / 4) * 4;
        int dataSize = rowSize * height;
        int fileSize = 14 + 40 + dataSize;

        std::ofstream file(name, std::ios::binary);

        // --- BMP Header ---
        file.put('B');
        file.put('M');
        file.write(reinterpret_cast<const char*>(&fileSize), 4);
        int reserved = 0;
        file.write(reinterpret_cast<const char*>(&reserved), 4);
        int offset = 14 + 40;
        file.write(reinterpret_cast<const char*>(&offset), 4);

        // --- DIB Header ---
        int headerSize = 40;
        file.write(reinterpret_cast<const char*>(&headerSize), 4);
        file.write(reinterpret_cast<const char*>(&width), 4);
        file.write(reinterpret_cast<const char*>(&height), 4);
        short planes = 1;
        file.write(reinterpret_cast<const char*>(&planes), 2);
        short bitsPerPixel = 24;
        file.write(reinterpret_cast<const char*>(&bitsPerPixel), 2);
        int compression = 0;
        file.write(reinterpret_cast<const char*>(&compression), 4);
        file.write(reinterpret_cast<const char*>(&dataSize), 4);
        int resolution = 0;
        file.write(reinterpret_cast<const char*>(&resolution), 4); // x pixels/meter
        file.write(reinterpret_cast<const char*>(&resolution), 4); // y pixels/meter
        int colorsUsed = 0;
        int importantColors = 0;
        file.write(reinterpret_cast<const char*>(&colorsUsed), 4);
        file.write(reinterpret_cast<const char*>(&importantColors), 4);

        // --- Image Data ---
        for (int y = 0; y < height; ++y) // BMP is bottom-up
        {
            for (int x = 0; x < width; ++x)
            {
                Pixel col = image.colourBuffer[y * width + x];
                unsigned char r = static_cast<unsigned char>(col.r * 255);
                unsigned char g = static_cast<unsigned char>(col.g * 255);
                unsigned char b = static_cast<unsigned char>(col.b * 255);
                file.put(b);
                file.put(g);
                file.put(r);
            }
            // Padding
            for (int i = 0; i < rowSize - 3 * width; ++i)
                file.put(0);
        }

        file.close();
    }
}