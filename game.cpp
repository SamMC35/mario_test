#include <dream.h>
#include "game.h"
#include "tilemap.h"
#include <iostream>
#include <sstream>

using namespace std;

bool init_done = false;

Texture map_1;

struct Player
{
   float x,y; 
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
    }

    stringstream title;

    title << "--BEGIN PLAY--";

    WriteStringText(title.str().c_str(), 28,300,200);
    if(init_timer.get_time() > 3000)
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

void Game::update()
{
    if(keyDown(SDL_SCANCODE_LEFT))
        player->x -= 3;
}

void Game::draw()
{
    RenderMap(&map_1);
}