#include "image.h"

image::image(int imgNum, int rot, std::vector<std::string> bound)
{
    imageNumber = imgNum;
    rotation = rot;
    boundaries = bound;
}