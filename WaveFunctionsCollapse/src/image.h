#ifndef IMAGE_H
#define IMAGE_H

#include<vector>
#include <string>

class image
{
private:
    int imageNumber;
    int rotation;
    std::vector<std::string> boundaries; 
public:
    image(int imgNum, int rot, std::vector<std::string> bound);
    ~image(){}; 
    int getImgNum()
    {
        return imageNumber;
    }
    int getRotation()
    {
        return rotation;
    }
    std::vector<std::string> getBoundaries()
    {
        return boundaries;
    }
};


#endif /*IMAGE*/