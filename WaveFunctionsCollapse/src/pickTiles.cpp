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
                    Tiles::pickMap[row][col]->ListOfAddedNeighbours.insert(Tiles::pickMap[newRow][newCol]);
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
    //Check if some of matching values are not in the TriedSet
    int len = Tiles::pickMap[row][col]->ListOfPossImgs.size();
    int del = 0;
    for(int i = 0; i<len; i++)   //For all poss
    {
        if(Tiles::pickMap[row][col]->SetOfTriedImgs.find(Tiles::pickMap[row][col]->ListOfPossImgs[i]) != Tiles::pickMap[row][col]->SetOfTriedImgs.end())    //If possibility is already tried
        {
           Tiles::pickMap[row][col]->ListOfPossImgs.erase(Tiles::pickMap[row][col]->ListOfPossImgs.begin()+i-del);     //Delete
            del++;
        }
    }
    //If one of neighbours is img 3 - > delete img 3 from poss
    bool meet = false;
    for(const auto&[rowChange, colChange]: dirs)    //For all dirs
    {
        int newRow = row + rowChange;
        int newCol = col + colChange;
        if(Tiles::InBound(newRow,newCol))       //Check if in bound
        {
            if(Tiles::pickMap[newRow][newCol]->collapsed == true)      //Check if collapsed
            {
                if(Tiles::pickMap[newRow][newCol]->imageObj->getImgNum() == 3)
                {
                    meet = true;
                    break;
                }
            }
        }
    }
    if(meet)
    {
        int len = Tiles::pickMap[row][col]->ListOfPossImgs.size();
        int del = 0;
        for(int i = 0; i<len; i++)   //For all poss
        {
            if(Tiles::pickMap[row][col]->ListOfPossImgs[i]->getImgNum() == 3)    //If possibility is already tried
            {
            Tiles::pickMap[row][col]->ListOfPossImgs.erase(Tiles::pickMap[row][col]->ListOfPossImgs.begin()+i-del);     //Delete
                del++;
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

/*
    Desc: Function recursivly tries to solve board.
    Uses backtracking in order to cope with wrong picks
    Parameters: -
*/
bool Tiles::Solve(std::vector<Tile*> &ListOfTilesToCollapse)
{
    while(!ListOfTilesToCollapse.empty())      //If some Tiles are left to collapse
    {
        /* Display */
        Graphics::ClearScreen(Graphics::g_main_renderer);
        Graphics::DisplayGrid();                                    //Display grid
        SDL_RenderPresent(Graphics::g_main_renderer);
        /* End of Display */


        Tiles::CountPossForListOfTilesToCollapse(); //Count the possibilites for the List and sort
        if(ListOfTilesToCollapse.back()->numOfPosImgs >0)    //If there are none Tiles with 0 poss
        {
            int randPick = rand() % ListOfTilesToCollapse.back()->numOfPosImgs;  //Pick randomly the imgae from possibilites
            ListOfTilesToCollapse.back()->imageObj =ListOfTilesToCollapse.back()->ListOfPossImgs[randPick];  //Set the image object to picked img
            ListOfTilesToCollapse.back()->SetOfTriedImgs.insert(ListOfTilesToCollapse.back()->imageObj);  //Add tried possibility to the Tile
            ListOfTilesToCollapse.back()->collapsed = true;  //Marked as collapsed
            int row = ListOfTilesToCollapse.back()->row, col = ListOfTilesToCollapse.back()->col;
            ListOfTilesToCollapse.pop_back();
            Tiles::UpdateListOfTilesToCollapse(row,col);    //Update the list of Tiles to collapse
            if(Solve(ListOfTilesToCollapse) == true)
            {
                return true;        //All Tiles completeted
            }
            else                    //Some Tile has 0 possibilites!
            {
                ListOfTilesToCollapse.push_back(Tiles::pickMap[row][col]);   //Push_back to the List of Tiles to Collpase
                Tiles::pickMap[row][col]->collapsed = false;    //Set to not collapsed
                Tiles::pickMap[row][col]->imageObj = nullptr;   //Reset imgae that is set to this Tile
                Tiles::DeleteFromListOfTilesToCollapse(row,col);
            }
        }
        else    //No possibilites for some Tile with current setup
        {
            ListOfTilesToCollapse.back()->SetOfTriedImgs.clear();    //Clear tried possibilites for that Tile
            //Tiles::visitedSet.erase({ListOfTilesToCollapse.back()->row,ListOfTilesToCollapse.back()->col});
            //Tiles::ListOfTilesToCollapse.pop_back();
            return false;   //Return false -> previous choice will be changed
        }
    }
    //List of Tiles to collapse is empty -> END
    /* Display */
    Graphics::ClearScreen(Graphics::g_main_renderer);
    Graphics::DisplayGrid();                                    //Display grid
    SDL_RenderPresent(Graphics::g_main_renderer);
    /* End of Display */
    std::cout<<"Your image has been created!"<<"\n"<<"Enjoy!"<<"\n";
    return true;    //All Tiles collapsed -> End!
}

/*
    Desc: Function to update the list Tiles which have at least one neighbour -> one boundary
    Parameters: int row, int col
*/
void Tiles::DeleteFromListOfTilesToCollapse(int row, int col)
{
    Tiles::ListOfTilesToCollapse.erase(std::remove_if(Tiles::ListOfTilesToCollapse.begin(), Tiles::ListOfTilesToCollapse.end(), [&](Tile* a) {      //Delete added neighbours from ListOfTilesToCollapse
        return Tiles::pickMap[row][col]->ListOfAddedNeighbours.find(a) != Tiles::pickMap[row][col]->ListOfAddedNeighbours.end();
    }), Tiles::ListOfTilesToCollapse.end());

    for(const auto&[rowChange, colChange]: dirs)    //For all dirs
    {
        int newRow = row + rowChange;
        int newCol = col + colChange;
        if(Tiles::InBound(newRow,newCol))       //Check if in bound
        {
            if(Tiles::pickMap[row][col]->ListOfAddedNeighbours.find(Tiles::pickMap[newRow][newCol]) != Tiles::pickMap[row][col]->ListOfAddedNeighbours.end())
            {
                visitedSet.erase({newRow,newCol});          //If added to visited delete it
            }
        }
    }

    Tiles::pickMap[row][col]->ListOfAddedNeighbours.clear();    //Clear set of added neighbours
}