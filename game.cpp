#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include "game.h"

int main( int argc, char* args[] )
{
	srand(time(0));
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//The dot that will be moving around on the screen
			Dot dot;

			//mapobject
			mapobject mapobject[5];
			for(int i=1;i<5;i++){
                mapobject[i].arrayinit(5,3,5,i);
                mapobject[i].reset();
			}

			//The background scrolling offset
			int scrollingOffset = 0;

			//start
			int start = 0;

			//The application timer
			LTimer timer;

			//In memory text stream
			std::stringstream timeText;


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
					//Handle input for the dot
					dot.handleEvent( e );
				}
				//Move the dot

				dot.move();
				for(int i=0;i<5;i++){
                    mapobject[i].checkcollision(dot);
                    mapobject[i].move(mapspeed);
                    mapobject[i].appmove(dot);
				}

				//Scroll background
				scrollingOffset+=mapspeed;

				if( scrollingOffset < -(gBGTexture.getWidth()) )
				{
				    dot.checkpoint();
				    for(int i=1;i<5;i++){
                        mapobject[i].reset();
                    }
                    dot.reset();
                    scrollingOffset = 0;
				}

				//Set text to be rendered
				timeText.str( "" );
				timeText << ( timer.getTicks() / 100 )<<" m" ;

				//Render text
				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), { 49, 49, 49 } ) )
				{
					printf( "Unable to render time texture!\n" );
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render background
				gBGTexture.render( scrollingOffset, 0 );
				gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

				//Render objects

				if(dot.isdown){
                    dot.render();
                    for(int i=1;i<5;i++){
                        mapobject[i].render(dot);
                    }
                    for(int i=1;i<5;i++){
                        mapobject[i].renderstack(dot);
                    }
				}else{
                    for(int i=1;i<5;i++){
                        mapobject[i].render(dot);
                    }
                    dot.render();
                    for(int i=1;i<5;i++){
                        mapobject[i].renderstack(dot);
                    }
				}


				while(start<1){
                    gTextTexture1.render( ( SCREEN_WIDTH - gTextTexture1.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture1.getHeight() ) / 2 );
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(1000);
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBGTexture.render( scrollingOffset, 0 );
                    gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                    //Render objects
                    dot.render();
                    gTextTexture2.render( ( SCREEN_WIDTH - gTextTexture2.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture2.getHeight() ) / 2 );
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(1000);
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBGTexture.render( scrollingOffset, 0 );
                    gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                    //Render objects
                    dot.render();
                    gTextTexture3.render( ( SCREEN_WIDTH - gTextTexture3.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture3.getHeight() ) / 2 );
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(1000);
                    //Clear screen
                    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                    SDL_RenderClear( gRenderer );

                    //Render background
                    gBGTexture.render( scrollingOffset, 0 );
                    gBGTexture.render( scrollingOffset + gBGTexture.getWidth(), 0 );

                    //Render objects
                    dot.render();
                    start++;
                    gFont = TTF_OpenFont( "pic/AGENCYB.ttf", 48 );
                    timer.start();
				}
				dot.checkborder(scrollingOffset);
                if(dot.isdead){
                    gTextTexture4.render( ( SCREEN_WIDTH - gTextTexture4.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture4.getHeight() ) / 2 );
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(3000);
                    break;
                }
                gTimeTextTexture.render( 0,0 );

				//Update screen
				SDL_RenderPresent( gRenderer );
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

