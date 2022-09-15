# Wave Function Collpase
You can read more about it here:
https://en.wikipedia.org/wiki/Wave_function_collapse

And visit GitHub repo about it:
https://github.com/mxgmn/WaveFunctionCollapse

## Result demo with backtracking
### More information with explenation below ⬇⬇⬇
![GIF animation of WFC algorithm](results/WithBacktracking/result.gif)  

## First working result - no backtracking
Used tiles:  
![Tile0](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/lines/0.png "Tile 0")
![Tile1](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/lines/1.png "Tile 1")
![Tile2](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/lines/2.png "Tile 2")  
After loading tiles with boundaries, algorithm computes all possible rotations. 
Example result for 5x5 grid:
![Result](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/results/V1%20-%20No%20backtracking/result.png "Result")
## Second example - no backtracking
Used tiles:  
![Tile0](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/0.png "Tile 0")
![Tile1](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/1.png "Tile 1")
![Tile2](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/2.png "Tile 2")
![Tile3](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/3.png "Tile 3")
![Tile4](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/4.png "Tile 4")
![Tile5](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/5.png "Tile 5")
![Tile6](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/6.png "Tile 6")
![Tile7](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/7.png "Tile 7")
![Tile8](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/8.png "Tile 8")
![Tile9](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/9.png "Tile 9")
![Tile10](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/10.png "Tile 10")
![Tile11](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/11.png "Tile 11")
![Tile12](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/12.png "Tile 12")
![Tile13](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/13.png "Tile 13")  
After loading tiles with boundaries, algorithm computes all possible rotations. 
Example result for 10x10 grid:
![Result](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/results/V1%20-%20No%20backtracking/circuitResult.png "Result")

## Third example - with implemented backtracking
Backtracking done recursivly by solve function  
Used tiles:  
![Tile0](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/0.png "Tile 0")
![Tile1](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/1.png "Tile 1")
![Tile2](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/2.png "Tile 2")
![Tile3](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/3.png "Tile 3")
![Tile4](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/4.png "Tile 4")
![Tile5](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/5.png "Tile 5")
![Tile6](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/6.png "Tile 6")
![Tile7](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/7.png "Tile 7")
![Tile8](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/8.png "Tile 8")
![Tile9](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/9.png "Tile 9")
![Tile10](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/10.png "Tile 10")
![Tile11](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/11.png "Tile 11")
![Tile12](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/12.png "Tile 12")
![Tile13](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/img/Circuit/13.png "Tile 13")  
After loading tiles with boundaries, algorithm computes all possible rotations. 
Example result for 40x40 grid:
![Result](https://github.com/nowakkuba99/SDL/blob/main/WaveFunctionsCollapse/results/WithBacktracking/circuitResultBacktrack.png "Result")
