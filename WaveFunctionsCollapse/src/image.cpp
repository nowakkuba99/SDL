#include "image.h"

image::image(int imgNum, int rot, std::vector<char> bound)
{
    imageNumber = imgNum;
    rotation = rot;
    boundaries = bound;
}