
#include<iostream>
#include<dream.h>
#include<cmath>
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

int GetTile(float x, float y)
{
    if(x < 0 || x > levelWidth)
        return 0;
    if(y < 0 || y > levelHeight)
        return 0;

    int x_int = abs(x);
    int y_int = abs(y);

    return level_data[y_int][x_int];
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

bool colgate(float x, float y)
{
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                if(Col_Check(tuple<int,int,int,int>(x,y,50,50),tuple<int,int,int,int>(i*50,j*50,50,50)))
                    return true;
            } 
        }
    }

    return false;
}


bool CollisionCheck(float x, float y)
{
    bool x_overlap, y_overlap, collision;
   for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i])
            {
                if((x >= (float) i && x <= i+0.99) && (y >= j & y <= j+0.99))
                    collision = true;
                
                if((x+0.99 >= (float) i && x+0.99 <= i+0.99) && (y >= (float)j & y <= (float)j+0.99))
                    collision = true;
                
                if((x >= (float) i && x <= i+0.99) && (y+0.99 >= (float)j & y+0.99 <= (float) j+0.99))
                    collision = true;

                if((x+0.99 >= (float) i && x+0.99 <=(float)(i+0.99)) && (y+0.99 >= (float)j & y+0.99 <= (float)j+0.99))
                    collision = true;

                if(collision)
                    return true;
            }
            else
            {
                continue;
            }
        }
    }
    return false;
}

bool RightCheck(float x, float y)
{
 
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                
                if((x+0.9 >= (float) i && x+0.9 <= (float)(i+1)) || (x >= (float) i && x <= (float)(i+1)))
                {
                    if(((y >= (float)j && y <= (float)(j+1))) ||(y + 1 >= (float)j && y + 1<= (float)(j+0.99)))
                        return true;
                }
                    //return true;
            } 
        }
    }

    return false;
}

bool LeftCheck(float x, float y)
{
 
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                if((x >= (float) i && x <= (float)(i+1)) || (x+0.9 >= (float) i && x+0.9 <= (float)(i+1)))
                    if((y >= (float)j && y <= (float)(j+1)) ||(y + 0.99 >= (float)j && y + 0.99<= (float)(j+1))) 
                        return true;
            } 
        }
    }

    return false;
}

bool VerticalCheck(float x, float y)
{
 
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                if((x >= (float) i*50 && x <= (float)(i+0.99)*50) && (y >= j*50 & y <= (float)(j+0.99)*50))
                    return true;
                if((x >= (float) i*50 && x <= (float)(i+0.99)*50) && (y+49 >= (float)j*50 && y + 49 <= (float)(j+0.99)*50))
                    return true;
                
            } 
        }
    }

    return false;
}

bool UpCheck(float x, float y)
{
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                if((x >= (float)i && x <= (float)(i+0.99)) && (y >= (float)j && y <= (float)(j+0.99)))
                    return true;
            } 
        }
    }

    return false;
}

bool DownCheck(float x, float y)
{
    for(int j = 0; j < levelHeight; j++)
    {
        for(int i = 0; i < levelWidth; i++)
        {
            if(level_data[j][i] == 1 || level_data[j][i] == 2)
            {
                if((x >= (float) i && x <= (float)(i+0.99)) && (y+1 >= (float)j && y + 1 <= (float)(j+0.99)))
                    return true;
            } 
        }
    }

    return false;
}
