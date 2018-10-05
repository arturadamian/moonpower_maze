#include "headers/maze.h"

/**
 * parseMap - parse map from an external file
 *
 * @worldMap: first map
 * @world2Map: second map
 */
void parseMap(int worldMap[mapHeight][mapWidth], int world2Map[mapHeight][mapWidth])
{
    ifstream inputFile("maps/map.txt");
    
    if (inputFile.is_open())
    {
        for (int a = 0; a < mapHeight; a++) {
            for (int b = 0; b < mapWidth; b++) {
                inputFile >> worldMap[a][b];
            }
        }
    }
    else
    {
        cout << "Couldn't read the map1 file" << endl;
    }
    inputFile.close();
    
    ifstream input2File("maps/map2.txt");
    if (input2File.is_open())
    {
        for (int i = 0; i < mapHeight; i++) {
            for (int j = 0; j < mapWidth; j++) {
                input2File >> world2Map[i][j];
            }
        }
    }
    else
    {
        cout << "Couldn't read the map2 file" << endl;
    }
    
    input2File.close();
}
