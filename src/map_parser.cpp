#include "../headers/maze.h"

void create_the_world(int worldMap[mapWidth][mapHeight])
{
    using namespace std;
    
    ifstream inputFile("maps/map.txt");
    if (inputFile.is_open())
    {
        for (int i = 0; i < 24; i++) {
            for (int j = 0; j < 24; j++) {
                inputFile >> worldMap[i][j];
            }
        }
    }
    else
        cout << "Couldn't read the map file" << endl;
    inputFile.close();
}


