#include "mission.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>

LTexture missiondefault;
LTexture missionpress;
LTexture sgold;
LTexture sscore;
LTexture sdistance;
LTexture mission1;
LTexture mission2;
LTexture mission3;
LButton home2;

std::stringstream goldmoney;
std::stringstream bestscore;
std::stringstream bestdistance;
std::stringstream m1d;
std::stringstream m2g;
std::stringstream m3p;

void substract()
{
    mis1-=distance;
    mis2-=asset;
    mis3-=score;
    if(mis1<0){
        m1+=1;
        mis1 = (2000+2000*m1);
        totalmoney+=25;
    }
    if(mis2<0){
        m2+=1;
        mis2 = (100+100*m2);
        totalmoney+=25;
    }
    if(mis3<0){
        m3+=1;
        mis3 = (100+100*m3);
        totalmoney+=25;
    }
}

void add()
{
    goldmoney.str("");
    bestscore.str("");
    bestdistance.str("");
    m1d.str("");
    m2g.str("");
    m3p.str("");
    goldmoney<<totalmoney;
    bestdistance<<highdistance;
    bestscore<<highscore;
    m1d<<mis1;
    m2g<<mis2;
    m3p<<mis3;
}

bool missionloadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	missiondefault. loadFromFile( "pic/mission1.png" );
	if( !missiondefault. loadFromFile( "pic/mission1.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	missionpress. loadFromFile( "pic/mission2.png" );
	if( !missionpress. loadFromFile( "pic/mission2.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	gFont = TTF_OpenFont( "pic/AGENCYB.ttf", 60 );
    //TTF_SetFontStyle(gfont, TTF_STYLE_BOLD);
    if( gFont == NULL )
    {
        printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
        success = false;
    }
    else
    {
        //Render text
        SDL_Color textColor = { 255, 255, 255 };
            if( !sgold.loadFromRenderedText( goldmoney.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !sdistance.loadFromRenderedText(bestdistance.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !sscore.loadFromRenderedText( bestscore.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !mission1.loadFromRenderedText( m1d.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !mission2.loadFromRenderedText( m2g.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }
            if( !mission3.loadFromRenderedText( m3p.str().c_str(), textColor ) ){
                printf( "Failed to render text texture!\n" );
                success = false;
            }

    }
    home2.setPosition(885,19);
    home2.BUTTON_HEIGHT = 104;
    home2.BUTTON_WIDTH = 104;
	return success;
}
void missionclose()
{
    missiondefault.free();
    sgold.free();
    sdistance.free();
    sscore.free();
    mission1.free();
    mission2.free();
    mission3.free();
}
void mission()
{
	//Start up SDL and create window
		//Load media
		add();
		if( !missionloadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;


           missiondefault.render(0,0);

			//While application is running
			while( !quit )
			{


               				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					home2.handleEvent(&e);
				}
                add();

                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                missiondefault.render(0,0);
                if(home2.show==true) missionpress.render(0,0);

				sgold.render(799,160);
                sscore.render(667,242);
                sdistance.render(667,323);
                mission1.render(405,460);
                mission2.render(405,548);
                mission3.render(405,637);//Update the surface
				SDL_RenderPresent( gRenderer );
				if(home2.press==true)  {home2.show=false; home2.press = false;break;}



			}
		}


	//Free resources and close SDL
	missionclose();

}
