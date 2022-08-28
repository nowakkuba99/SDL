#ifndef TILE_H // include guard
#define TILE_H

#include <vector>
class Tile
{
private:
    /* data */
    int imgNumber;
    int rotation;
    int numOfPosNeig;
    std::vector<int> PosNeig;
public:
    Tile();
    Tile(int num, int rot): imgNumber(num), rotation(rot){};
    ~Tile();
    int getImgNum()
    {
        return imgNumber;
    }
    void setImgNum(int num)
    {
        imgNumber = num;
    }
    int getRotation()
    {
        return rotation;
    }
    void setRotation(int rot)
    {
        rotation = rot;
    } 
};
#endif /* TILE */