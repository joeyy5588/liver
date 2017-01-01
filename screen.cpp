#include "screen.h"
#include "map.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;

int start_count = 0;

//Scene textures
LTexture gDotTexture1;
LTexture gDotTexture2;
LTexture gBGTexture;
LTexture gTextTexture1;
LTexture gTextTexture2;
LTexture gTextTexture3;
LTexture gTextTexture4;
LTexture gTimeTextTexture;
LTexture gPausePromptTexture;
LTexture gStartPromptTexture;
LTexture gMoneyTexture;
LTexture gBuildingTexture1;
LTexture gBuildingTexture2;
LTexture gPeopleTexture1;
LTexture gPeopleTexture2;
LTexture gPeopleTexture3;
LTexture gPeopleTexture12;
LTexture gPeopleTexture22;
LTexture gPeopleTexture32;



bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
		{
			printf( "Warning: Linear texture filtering not enabled!" );
		}

		//Create window
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( gWindow == NULL )
		{
			printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
			if( gRenderer == NULL )
			{
				printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}
				//Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
                    success = false;
                }

			}
		}
	}

	return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load dot texture
	if( !gDotTexture1.loadFromFile( "pic/trump_D.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gDotTexture2.loadFromFile( "pic/trump_U.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
    if( !gMoneyTexture.loadFromFile( "pic/coin_2.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gBuildingTexture1.loadFromFile( "pic/Empire_State_Building.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gBuildingTexture2.loadFromFile( "pic/NewYorkCity_StatueOfLiberty.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture1.loadFromFile( "pic/white_D.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture2.loadFromFile( "pic/mexican_D.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture3.loadFromFile( "pic/african_D.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture12.loadFromFile( "pic/white_U.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture22.loadFromFile( "pic/mexican_U.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	if( !gPeopleTexture32.loadFromFile( "pic/african_U.png" ) )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}
	//Load background texture
	if( !gBGTexture.loadFromFile( "pic/map2.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}
	//Load pause state
	if( !gPausePromptTexture.loadFromFile( "pic/pause.png" ) )
	{
		printf( "Failed to load background texture!\n" );
		success = false;
	}


    //Open the font
    gFont = TTF_OpenFont( "pic/AGENCYB.ttf", 150 );
    //TTF_SetFontStyle(gfont, TTF_STYLE_BOLD);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 49, 49, 49 };
            if( !gTextTexture1.loadFromRenderedText( "3", textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !gTextTexture2.loadFromRenderedText( "2", textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !gTextTexture3.loadFromRenderedText( "1", textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !gTextTexture4.loadFromRenderedText( "YOU LOSE", textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            //Load stop prompt texture
            if( !gStartPromptTexture.loadFromRenderedText( "Press S to Start or Stop the Timer", textColor ) )
            {
                printf( "Unable to render start/stop prompt texture!\n" );
                success = false;
            }
    }
	return success;
}

void close()
{
	//Free loaded images
	gDotTexture1.free();
	gDotTexture2.free();
	gBGTexture.free();
    gTextTexture1.free();
    gTextTexture2.free();
    gTextTexture3.free();
    gTextTexture4.free();
    gTimeTextTexture.free();
	gStartPromptTexture.free();
	gPausePromptTexture.free();
	gMoneyTexture.free();
	gBuildingTexture1.free();
	gBuildingTexture2.free();
    gPeopleTexture1.free();
    gPeopleTexture2.free();
    gPeopleTexture3.free();

    //Free global font
    TTF_CloseFont( gFont );
    gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
    TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

