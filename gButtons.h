#ifndef GBUTTONS_H
#define GBUTTONS_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "map.h"
#include "screen.h"
//Button constants




class LButton
{
    friend  bool  menuloadMedia();
    friend  bool  shoploadMedia();
    friend  bool  missionloadMedia();

    friend  void shopclose();
    friend  void missionclose();
    friend  void menuclose();

	public:
		//Initializes internal variables
		LButton();

		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		void handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();

        bool show;

        bool press;

        int BUTTON_WIDTH;
        int BUTTON_HEIGHT;
		//Top left position
		SDL_Point mPosition;

		//Currently used global sprite
     	LTexture  mCurrentsurface;
};



#endif
