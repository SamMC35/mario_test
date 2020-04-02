#ifndef GAME_H
#define GAME_H

class Game 
{
public:
    int state;

    Game();

    void init();        //Initialize everything
    void update();      //Update everything
    void menu();        //Menu draw
    void draw();        //Draw the game
};

void kill();
#endif