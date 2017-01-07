#ifndef CHARACTER_H
#define CHARACTER_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include "trump.h"

//map moving speed
extern int mapspeed ;
extern int asset;
extern int score;
extern int distance;
extern int triggeredtime;
extern bool triggered;

class trump
{
    public:
        trump(){highscore = 0; billionaire=time=champion=superman=angel=false;}
        int highscore;
        bool billionaire;
        bool time;
        bool champion;
        bool superman;
        bool angel;

};
class Dot
{
    friend class money;
    friend class obstacle;
    friend class people;
    friend class mapobject;
    public:
		//The dimensions of the dot
		static const int DOT_WIDTH = 119;
		static const int DOT_HEIGHT = 127;

		//Maximum axis velocity of the dot
		static const int DOT_VEL = 10;
        int direction=0;
		//Initializes the variables
		Dot();

		//Takes key presses and adjusts the dot's velocity
		void handleEvent( SDL_Event& e );

		//Moves the dot
		void move();

		//Shows the dot on the screen
		void render();

		//check if the dot is out of border
		bool checkborder(int &);

		//The direction of Trump
		bool isdown;

		//alive or dead
		bool isdead;

		//stack on trump
		int stack[20]={0};

		//reset stack
		void reset();

		//checkpoint;
		void checkpoint();

		void mapevent(int);

    private:
		//The X and Y offsets of the dot
		int mPosX, mPosY;

		//The velocity of the dot
		int mVelX, mVelY;
};
#endif
