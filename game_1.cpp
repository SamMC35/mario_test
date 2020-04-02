#include <dream.h>
#include "game.h"
#include "tilemap.h"
#include <iostream>
#include <sstream>

using namespace std;

bool init_done = false;

bool sign(float x)
{
    if(x < 0)
        return -1;
    else if (x>0)
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
        
        player->x = 200;
        player->y = 300;
        
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

int xVel, yVel = 0;

void Game::update()
{
    xVel = -(keyDown(SDL_SCANCODE_LEFT)) + keyDown(SDL_SCANCODE_RIGHT);

    yVel = keyDown(SDL_SCANCODE_X);
    
    player->hsp = xVel * 7;
    //Horizontal check
   
    /*
    for(int i = 0; i < num_step; i++)
    {
        player->x += xVel * step_vel;
        
        if(HorizontalCheck(player->x, player->y))
        {
            player->x = oldx;
        }
    }*/

    
    
    //Vertical check
    if(player->vsp < 10) 
        player->vsp += 0.2;

    if(VerticalCheck(player->x, player->y+50))
    {
       player->vsp = yVel * -8;
    }
 
    if(HorizontalCheck((player->x + player->hsp), player->y))
    {
        while(!HorizontalCheck((player->x + sign(player->hsp)), player->y))
            player->x += sign(player->hsp);
        
        player->hsp = 0;
    }
    
    if(VerticalCheck(player->x, (player->y + player->vsp)))
    {
        while(!VerticalCheck(player->x, (player->y+sign(player->vsp))))
            player->y += sign(player->vsp);
        
        player->vsp = 0;
    }
    
    player->x += player->hsp;
    player->y += player->vsp;
    //Gravity
    
    

    
        
    
    cout << player->vsp <<endl;
}

void Game::draw()
{
    RenderMap(&map_1);
    DrawSurfaceQuad((int)(player->x), (int)(player->y), 50,50,255,0,255);
}