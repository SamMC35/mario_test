
#include<iostream>
#include<dream.h>
#include<fstream>

FILE *level;

using namespace std;

int level_data[12][16];
Texture map;

int levelHeight = 12, levelWidth = 16;

void fileRead(char* path)
{

    level = fopen(path, "r");
    for(int i = 0; i < levelHeight; i++)
    {
        for(int j = 0; j < levelWidth; j++)
        {
            fscanf(level,"%d ", &level_data[i][j]);
        }
    }
    fclose(level);
}

void RenderMap(Texture* map)
{
    DrawSurfaceQuad(0,0,800,600,164,228,252);
    for(int y = 0; y < levelHeight; y++)
    {
        for(int x = 0; x < levelWidth; x++)
        {
            switch(level_data[y][x])
            {
                case 1:     //Brick 1
                    LoadSpritesCropped(map,x*50,y*50,50,50,0,0,16,16);
                    break;
                case 2:     //Brick 2
                    LoadSpritesCropped(map,x*50,y*50,50,50,16,0,16,16);
                    break;
                default:
                    break;
            }
        }
    }
}


