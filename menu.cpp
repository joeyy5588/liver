
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "menu.h"



LButton menus[4];
LTexture menudefault;


bool menuloadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
	menudefault. loadFromFile( "pic/menu0.png" );
	if( !menus[0].mCurrentsurface. loadFromFile( "pic/menu0.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}
	menus[0].mCurrentsurface. loadFromFile( "pic/menu1.png" );
	if( !menus[0].mCurrentsurface. loadFromFile( "pic/menu1.png" ) )
	{
		printf( "Failed to load button sprite texture!\n" );
		success = false;
	}

   menus[1].mCurrentsurface.loadFromFile( "pic/menu2.png" );
	if(!menus[1].mCurrentsurface.loadFromFile( "pic/menu2.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

   menus[2].mCurrentsurface.loadFromFile( "pic/menu3.png" );
	if(! menus[2].mCurrentsurface.loadFromFile( "pic/menu3.png" ))
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}


	menus[3].mCurrentsurface.loadFromFile( "pic/menu4.png" );
	if( !menus[3].mCurrentsurface.loadFromFile( "pic/menu4.png"  ))
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	menus[0].setPosition(767,165);
    menus[1].setPosition(784,295);
    menus[2].setPosition(682,410);
    menus[3].setPosition(817,537);
    menus[0].BUTTON_HEIGHT = 130;
    menus[1].BUTTON_HEIGHT = 115;
    menus[2].BUTTON_HEIGHT = 127;
    menus[3].BUTTON_HEIGHT = 117;
    menus[0].BUTTON_WIDTH = 1024-767;
    menus[1].BUTTON_WIDTH = 1024-784;
    menus[2].BUTTON_WIDTH = 1024-682;
    menus[3].BUTTON_WIDTH = 1024-817;

	return success;
}

void menuclose()
{
	//Deallocate surfaces
	for( int i = 0; i < 4; ++i )
	{
		 menus[ i ].mCurrentsurface.free();

	}

	 menudefault.free();
}



int menu()
{
    int turn=0;

	//Start up SDL and create window


		//Load media
		if( !menuloadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;


           menudefault.render(0,0);

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

					//Handle button events
					for( int i = 0; i < 4; ++i )
					{
						menus[ i ].handleEvent( &e );
					}
				}


            SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
            SDL_RenderClear( gRenderer );
                menudefault.render(0,0);

             for( int i = 0; i <4; ++i )
				{ if(menus[i].show==true)
					menus[ i ].render();
				}

				//Update the surface
				SDL_RenderPresent( gRenderer );
				if(menus[0].press==true) {menus[0].press=false;turn=1; break; }
                if(menus[1].press==true) {menus[1].press=false;turn=2; break; }
                if(menus[2].press==true) {menus[2].press=false;turn=3; break; }
                if(menus[3].press==true) {menus[3].press=false;turn=4; break; }


			}
		}


	//Free resources and close SDL
	menuclose();

	return turn;
}
