#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "shop.h"


LTexture buydefault;
LButton shopdefault[2];
LButton buy[2];
LButton gButtons[ 5 ];
LButton home;

bool  shoploadMedia()
{
	//Loading success flag
	bool success = true;

	//Load default surface
    gButtons[1].mCurrentsurface.loadFromFile( "shoptime.bmp" );
	if( !gButtons[1].mCurrentsurface.loadFromFile( "shoptime.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	gButtons[0].mCurrentsurface.loadFromFile( "shopmillion.bmp" );
	if( !gButtons[0].mCurrentsurface.loadFromFile( "shopmillion.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	gButtons[2].mCurrentsurface.loadFromFile( "shopsuper.bmp" );
	if( !gButtons[2].mCurrentsurface.loadFromFile( "shopsuper.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	gButtons[3].mCurrentsurface.loadFromFile( "shopsuper.bmp" );
	if( !gButtons[3].mCurrentsurface.loadFromFile( "shopsuper.bmp"  ))
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	gButtons[4].mCurrentsurface.loadFromFile( "shopheat.bmp" );
	if( !gButtons[4].mCurrentsurface.loadFromFile( "shopheat.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

    buy[0].mCurrentsurface.loadFromFile( "buyyes.bmp" );
	if( !buy[0].mCurrentsurface.loadFromFile( "buyyes.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
    buy[1].mCurrentsurface.loadFromFile( "buyno.bmp" );
	if(!buy[1].mCurrentsurface.loadFromFile( "buyno.bmp" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	buydefault.loadFromFile( "buyask.bmp" );
	shopdefault[0].mCurrentsurface.loadFromFile( "shopdefault.bmp" );
    home.mCurrentsurface.loadFromFile("shophome.bmp");
    gButtons[0].setPosition(900,110);
    gButtons[1].setPosition(900,220);
    gButtons[2].setPosition(900,330);
    gButtons[3].setPosition(900,440);
    gButtons[4].setPosition(900,600);
    buy[0].setPosition(300,450);
    buy[1].setPosition(550,450);
    home.setPosition(900,0);
    shopdefault[0].setPosition(50,50);
    shopdefault[1].setPosition(50,50);
	return success;
}

void shopclose()
{
	//Deallocate surfaces
	for( int i = 0; i < 5; ++i )
	{
		 gButtons[ i ].mCurrentsurface.free();

	}
    for( int i = 0; i < 2; ++i )
	{
		 buy[i].mCurrentsurface.free();

	}
	 buydefault.free();
	 shopdefault[0].mCurrentsurface.free();
	 shopdefault[1].mCurrentsurface.free();
	 home.mCurrentsurface.free();


}





int shop()
{

		//Load media
		if( !shoploadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

            start:
            shopdefault[0].render();

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
					  shopdefault[0].render();
                      home.handleEvent(&e ); if(home.show=true)  home.render();
					//Handle button events
					for( int i = 0; i < 5; ++i )
					{
						gButtons[ i ].handleEvent(&e );
					}
				}
             for( int i = 0; i <5; ++i )
            { if(gButtons[i].show==true)
              {gButtons[ i ].render();}
            }

			for( int i = 0; i < 5; ++i )
			{if(gButtons[i].press==true)
              {  gButtons[i].press=false; int ability=i;
                  buydefault.render(0,0);
                 while( !quit )
                 {while( SDL_PollEvent( &e ) != 0 )
                 {for( int i = 0; i < 2; ++i )
					{
						buy[ i ].handleEvent( &e );
					}
                 for( int i = 0; i <2; ++i )
               { if(buy[i].show==true)
                  buy[ i ].render();
               }
              if(buy[0].show==false&&buy[1].show==false)   buydefault.render(0,0);
               SDL_RenderPresent( gRenderer );

                /*if(buy[0].press==true) { people.coin-=100;buy[0].press=false;
                switch(ability){
                  case 0: {people.billionaire=true;goto  start;}
                  case 1: { people.time=true;goto  start;}
                  case 2:  {people.champion=true;goto  start;}
                   case 3: {people.superman=true;goto  start;}
                   case 4: {people.angel=true;goto  start;}
                } }*/
                if(buy[1].press==true) {buy[1].press=false; goto  start;}
              }}

				}
				if(home.press==true) { home.press=false;goto close;}
				SDL_RenderPresent( gRenderer );

				//Update the surface

			}
		}}

  close:
	shopclose();

	return 0;
}
