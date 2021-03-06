#include <dream.h>
#include "game.h"
#include "tilemap.h"
#include <iostream>
#include <sstream>

using namespace std;

bool init_done = false;

Timer pl_timer;

bool sign(float x)
{
    if(x < 0.0)
        return -1;
    else if (x>0.0)
        return 1;
    else   
        return 0;
}

Texture map_1;

struct Player
{
   float x,y;		//x and y co-ordinates
   
   float hsp, vsp; 	//Horizontal speed and Vertical speed
   
   bool grounded;	//Grounded or not
};

Player *player = new Player();

Game::Game()
{
    state = 1;
}

Timer init_timer;

void Game::init()
{
    //Initializes everything
    if(!init_done)
    {
        fileRead((char*)"maps/level_1_1.mpk");
        map_1.loadFile((char*)"sprites/tileset.bmp");
        init_done = true;
        init_timer.reset_time();
        
        player->x = 4;
        player->y = 10;
        
        player->hsp = 0;
        player->vsp = 0;
        player->grounded = true;
    }

    stringstream title;

    title << "--BEGIN PLAY--";

    WriteStringText(title.str().c_str(), 28,300,200);
    if(init_timer.get_time() > 300)
        state = 3;
}


void Game::menu()
{
    //Draws menu
    stringstream title;

    title << "--MENU--";

    WriteStringText(title.str().c_str(), 40,300,200);

    if(keyDown(SDL_SCANCODE_RETURN))
        state = 2;
}
void Game::draw()
{
    RenderMap(&map_1);
    DrawSurfaceQuad((int)(player->x*50), (int)(player->y*50), 50,50,255,0,255);
}

float xVel = 0, yVel = 0;
bool grounded;

void Game::update()
{
    //xVel = -(keyDown(SDL_SCANCODE_LEFT)) + keyDown(SDL_SCANCODE_RIGHT);

 
    //yVel = -(keyDown(SDL_SCANCODE_UP)) + keyDown(SDL_SCANCODE_DOWN);

    float deltaTime = (float)pl_timer.get_time()/100 ;
    pl_timer.reset_time();

    if(keyDown(SDL_SCANCODE_LEFT))
        xVel = -1.0f;

    if(keyDown(SDL_SCANCODE_RIGHT))
        xVel = 1.0f;

    if(!keyDown(SDL_SCANCODE_LEFT) && !keyDown(SDL_SCANCODE_RIGHT))
        xVel = 0.0f;
        
    if(keyDown(SDL_SCANCODE_X))
    {
        yVel = -1.0f;
    }  


    if(!grounded)
    {
        yVel += 0.1f;
    }  

    float newx = player->x + xVel * deltaTime;
    float newy = player->y + yVel * deltaTime;

    if(xVel <= 0)
    {
        if(GetTile(newx+0.0f,player->y+0.0f)|| GetTile(newx+0.0f,player->y+0.9f))
        {
            cout << "left";
            newx = (int) newx+1;
            xVel = 0;
        }
    }
    else
    {
        if(GetTile(newx+1.0f,player->y+0.0f)|| GetTile(newx+1.0f,player->y+0.9f))
        {
            cout << "right";
            newx = (int) newx;
            xVel = 0;
        }
    }

    bool grounded = false;

    if(yVel <= 0)
    {
        if(GetTile(newx+0.0f,newy)|| GetTile(newx+0.9f,newy))
        {
            cout << "up";
            newy = (int) newy+1;
            yVel = 0;
        }
    }
    else
    {
        if(GetTile(newx+0.0f,newy+1.0f)|| GetTile(newx+0.9f,newy+1.0f))
        {
            cout << "down";
            newy = (int)newy;
            grounded = true;
            yVel = 0;
        }
    }


    player->x = newx;
    player->y = newy;
    //Horizontal movement

    cout << "del: "<<deltaTime<<endl; 
    cout << "XVEL:" <<xVel <<endl;
    cout << "YVEL:" <<yVel <<endl;
    
    //Horizontal motion


}


