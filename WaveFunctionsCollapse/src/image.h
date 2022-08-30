#ifndef IMAGE_H
#define IMAGE_H

#include<vector>

class image
{
private:
    int imageNumber;
    int rotation;
    std::vector<char> boundaries; 
public:
    image(int imgNum, int rot, std::vector<char> bound);
    ~image(){}; 
    int getImgNum()
    {
        return imageNumber;
    }
    int getRotation()
    {
        return rotation;
    }
};


#endif /*IMAGE*/