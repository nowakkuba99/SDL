#include "pickTiles.h"
#include <iostream>
#include <algorithm>
/* Variables */
std::vector<std::vector<Tile*> > Tiles::pickMap(GRID_SIZE_H,std::vector<Tile*>(GRID_SIZE_W));
std::vector<Tile*> Tiles::ListOfTilesToCollapse;
std::set<std::pair<int,int> > Tiles::visitedSet;

/* FUNCTIONS */

/*
    Desc: Function to create Tile objects at the whole grid 
    Parameters: -
*/
void Tiles::InitTilesMap()
{
    /* Initi map */
    for(int row = 0; row<GRID_SIZE_H; row++)
    {
        for(int col = 0; col<GRID_SIZE_W; col++)
        {
            Tiles::pickMap[row][col] = new Tile(row,col);
        }
    }
}
/*
    Desc: Function to pick the first Tile
    Parameters: -
*/
void Tiles::PickFirstTile()
{
    /* Randomly pick image for first tile (top left corner) */
    srand(time(0));
    int randPick = rand() % Graphics::NUMBER_OF_IMG_WITH_ROTATED;   //Pick rand image
    int row = 0, col = 0;
    visitedSet.insert({row,col});
    Tiles::pickMap[row][col]->imageObj = Graphics::imgArr[randPick];    //Assign image to tile
    Tiles::pickMap[row][col]->collapsed = true;     //Set Tile to collapsed
    Tiles::pickMap[row][col]->numOfPosImgs = 1;     //Set number of possible imgs to 1
    Tiles::UpdateListOfTilesToCollapse(row,col);    //Update the list of Tiles to collapse
}
/*
    Desc: Function to check if given row and col are ine range
    Parameters: int row, int col
*/
bool Tiles::InBound(int row, int col)
{
    if(row >= 0 && row < GRID_SIZE_H)
        if(col >=0 && col < GRID_SIZE_W)
            return true;
    return false;
}
/*
    Desc: Function to update the list Tiles which have at least one neighbour -> one boundary
    Parameters: int row, int col
*/
void Tiles::UpdateListOfTilesToCollapse(int row, int col)
{
    for(const auto&[rowChange, colChange]: dirs)    //For all dirs
    {
        int newRow = row + rowChange;
        int newCol = col + colChange;
        if(Tiles::InBound(newRow,newCol))       //Check if in bound
        {
            if(Tiles::pickMap[newRow][newCol]->collapsed == false)      //Check if not collapsed
                if(visitedSet.find({newRow, newCol}) == visitedSet.end())
                {
                    ListOfTilesToCollapse.push_back(Tiles::pickMap[newRow][newCol]);    //Add to the list to collapse
                    visitedSet.insert({newRow,newCol});
                }
        }
    }
}
/*
    Desc: Function to update the list of possibiliteis of given Tile at row,col
    Parameters: int row, int col
*/
void Tiles::UpdateListOfPoss(int row, int col)
{
    std::vector<std::string> curr;
    std::vector<std::string> curr1(4);
    int dir = 0;    //0 - right, down, left, up
    for(const auto&[rowChange, colChange]: dirs)    //For all dirs
    {
        int newRow = row + rowChange;
        int newCol = col + colChange;
        if(Tiles::InBound(newRow,newCol))       //Check if in bound
        {
            if(Tiles::pickMap[newRow][newCol]->collapsed == true)      //Check if collapsed
            {
                curr.push_back(Tiles::pickMap[newRow][newCol]->imageObj->getBoundaries()[dir]);
            }
            else
                curr.push_back("-");
        }
        else
            curr.push_back("-");
        dir++;
    }
    curr1[0] = curr[2];
    curr1[1] = curr[3];
    curr1[2] = curr[0];
    curr1[3] = curr[1];
    //For all 4 boundaries
    for(auto  &bound: curr1)
    {
        std::reverse(bound.begin(), bound.end());   //Reverse boundaries in order to cope with not symetrical tiles
    }
    curr = curr1;
    //Now curr is the bound arr e.g. ["-","ABBA","-","ABAB"]
    Tiles::pickMap[row][col]->ListOfPossImgs.clear();   //Clear the vector to do update
    for(int i =0; i <curr.size(); i++)  //For all four dirs
    {
        if(curr[i] != "-")      //If neighbour it that dir is collapsed
        {
            if(Tiles::pickMap[row][col]->ListOfPossImgs.empty())    //If list of poss neigh empty
            {
                for(int j = 0; j<Graphics::imgArr.size();j++)   //Check all imgs
                {
                    if(Graphics::imgArr[j]->getBoundaries()[i] == curr[i])
                    {
                        Tiles::pickMap[row][col]->ListOfPossImgs.push_back(Graphics::imgArr[j]);    //Add such that fit curr bound
                    }
                }
            }
            else    //Some possiblities in list
            {
                int len = Tiles::pickMap[row][col]->ListOfPossImgs.size();
                int del = 0;
                for(int j = 0; j<len;j++)   //For all poss
                {
                    if(Tiles::pickMap[row][col]->ListOfPossImgs[j-del]->getBoundaries()[i] != curr[i])  //If not match
                    {
                        Tiles::pickMap[row][col]->ListOfPossImgs.erase(Tiles::pickMap[row][col]->ListOfPossImgs.begin()+j-del);     //Delete
                        del++;
                    }
                }
            }
        }
    }
    //At last update num
    Tiles::pickMap[row][col]->numOfPosImgs = Tiles::pickMap[row][col]->ListOfPossImgs.size();
}

/*
    Desc: Function to update the list of possibiliteis of given Tile at row,col
    Parameters: int row, int col
*/
void Tiles::CountPossForListOfTilesToCollapse()
{
    //Update list off poss
    for(int i = 0; i< ListOfTilesToCollapse.size(); i++)
    {
        UpdateListOfPoss(ListOfTilesToCollapse[i]->row, ListOfTilesToCollapse[i]->col);
    }
    //Sort the list with lambda functions by the number of possibilites
    sort(ListOfTilesToCollapse.begin(), ListOfTilesToCollapse.end(), 
    [](const Tile* a, const Tile* b) -> bool
    { 
        return a->numOfPosImgs > b->numOfPosImgs; 
    });
}