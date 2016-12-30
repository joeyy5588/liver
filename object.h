#ifndef OBJECT_H
#define OBJECT_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>
#include <ctime>
#include "screen.h"
#include "character.h"

class money
{
        friend class mapobject;
        public:
        //check if money is valid in this map
        int isvalid;
        //Shows the dot on the screen
        void render();
		//check if trump reach money
		void checkcollision(Dot&);
		//Moves the dot
		void move(int &);
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;
		//The velocity of the dot
		int mVelX, mVelY;

};
class obstacle
{
    friend class mapobject;
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;
		//The velocity of the dot
		int mVelX, mVelY;
		//which building to show
		int buildingtype;
    public:
        obstacle(){isvalid = mVelX = mVelY = mPosX = mPosY = 0; buildingtype = rand()%2;}
        //whether to show the obstacle
        int isvalid;
        //Shows the dot on the screen
        void render();
		//Moves the dot
		void move(int &);
		//check if trump reach money
		void checkcollision(Dot&);

};
class people
{
    friend class mapobject;
    private:
        //The X and Y offsets of the dot
		int mPosX, mPosY;
		//The velocity of the dot
		int mVelX, mVelY;
		//which building to show
		int peopletype;
    public:
        people(){isvalid = mVelX = mVelY = mPosX = mPosY = 0; peopletype = rand()%3;}
        //whether to show the obstacle
        int isvalid;
        //Shows the dot on the screen
        void render();
		//Moves the dot
		void move(int &);
		//check if trump reach money
		void checkcollision(Dot&);

};
class mapobject
{
    private:
        int m, o, p;
    public:
        mapobject(){m=o=p=mapcount=0;}
        void arrayinit(int , int , int , int );
        //state objects' x position
        int objectpositionx[25]={0};
        //state objects' y position
        int objectpositiony[25]={0};
        //state object's type
        int objecttype[20]={0};
        //check
        bool checkobjectrepeat(int, int);
        void move(int &);
        void render();
        void reset();
        money mapmoney[25];
        obstacle mapobstacle[25];
        people mappeople[25];
        //check if trump reach money
		void checkcollision(Dot&);


    protected:
        int mapcount;


};

#endif
