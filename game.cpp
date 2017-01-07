#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <iomanip>
#include <SDL_ttf.h>
#include "game.h"
#include <windows.h>

double lastTime = 0;
double nowTime = 0;
double unprocessedstartTime = 0;
double unprocessedendTime = 0;
double pauseTime = 0;
int abstartTime = 0;
int abnowTime = 0;
int dtime = 0;
bool halfquit = false;

void normalmode()
{
    lastTime = SDL_GetTicks();
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

    //In memory text stream
    std::stringstream timeText;
    std::stringstream timeText2;
    std::stringstream timeText3;

    int turn = 0;
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
            }else if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                //Adjust the velocity
                switch( e.key.keysym.sym )
                {
                    case SDLK_p: pausemode(); break;
                }
                if(halfquit){
                    return;
                }
            }
            //Handle input for the dot
            dot.handleEvent( e );
        }


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
        nowTime = SDL_GetTicks()-3000;
        timeText <<"Score: "<<std::setw(8)<<score<<"      "<<"Gold: $ "<<std::setw(8)<<asset
        << "        Distance: "<<std::setw(8)<<(int)( ((nowTime-lastTime)-pauseTime) / 100 );
        int tempdistance ;
        tempdistance = (int)( ((nowTime-lastTime)-pauseTime) / 100 );
        //timeText2 << "Distance: "<<"            "<<"m"<<"            "<<"Score: "<<"            "<<"$ ";
        /*timeText3 << "                    "<<score<<"                    "<<asset;*/
        unprocessedendTime = unprocessedstartTime =0;


        //Render text
        if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), { 49, 49, 49 } ) )
        {
            printf( "Unable to render time texture!\n" );
        }
        /*if( !gTimeTextTexture2.loadFromRenderedText( timeText2.str().c_str(), { 49, 49, 49 } ) )
        {
            printf( "Unable to render time texture!\n" );
        }
        if( !gTimeTextTexture3.loadFromRenderedText( timeText3.str().c_str(), { 49, 49, 49 } ) )
        {
            printf( "Unable to render time texture!\n" );
        }*/

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
        }
        if(tempdistance>1500) mapspeed = -6;
        if(tempdistance==(500+500*triggeredtime)) {
            triggered = true;
            abstartTime = SDL_GetTicks();
            triggeredtime++;
        }
        abnowTime = SDL_GetTicks();
        dtime = abnowTime - abstartTime;
        if(billionaire||timemachine||champion||superman){

            dot.mapevent(dtime);
        }
        dot.checkborder(scrollingOffset);
        if(dot.isdead){
            Mix_PlayChannel( -1, gdead, 0 );
            distance = (int)( ((nowTime-lastTime)-pauseTime) / 100 );
            gTextTexture4.render( ( SCREEN_WIDTH - gTextTexture4.getWidth() ) / 2, ( SCREEN_HEIGHT - gTextTexture4.getHeight() ) / 2 );
            SDL_RenderPresent( gRenderer );
            SDL_Delay(3000);
            break;
        }

        gTimeTextTexture.render( 0,0 );
        /*gTimeTextTexture2.render( SCREEN_WIDTH/2-200,0 );
        gTimeTextTexture3.render( 0,0 );*/

        //Update screen
        SDL_RenderPresent( gRenderer );
    }
}

void pausemode()
{
    //Main loop flag
    bool pausestate = true;
    //Event handler
    SDL_Event e;

    //Calculate the paused ticks
    unprocessedstartTime = SDL_GetTicks();

    while(pausestate){
        while( SDL_PollEvent( &e ) != 0 )
            {
                if( e.type == SDL_KEYDOWN && e.key.repeat == 0 ){
                    //Adjust the velocity
                    switch( e.key.keysym.sym )
                    {
                        case SDLK_p: pausestate = false; break;
                        case SDLK_q: pausestate = false; halfquit = true; break;
                    }
                }
            }
        //Clear screen
        SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
        SDL_RenderClear( gRenderer );

        gPausePromptTexture.render(0,0);

        //Update screen
        SDL_RenderPresent( gRenderer );


    }
    //Reset the paused ticks
    unprocessedendTime = SDL_GetTicks();
    pauseTime+=(unprocessedendTime-unprocessedstartTime);
}

void reset()
{
    asset = 0;
    score = 0;
    distance = 0;
    nowTime = 0;
    lastTime = 0;
    pauseTime = 0;
    triggeredtime = 0;
    halfquit = false;
}

int main( int argc, char* args[] )
{
	HWND hWnd = GetConsoleWindow();
    ShowWindow( hWnd, SW_HIDE );
	loadfile();
	srand(time(0));
	//The application timer
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
			Mix_VolumeMusic(MIX_MAX_VOLUME/2);
			Mix_PlayMusic( gMusic, -1 );
			int a;
			do{
                a = menu();
                switch(a){
                    case 1:
                        Mix_VolumeMusic(MIX_MAX_VOLUME/4);
                        normalmode();
                        if(!halfquit){
                            totalmoney+=asset;
                            if(score>highscore) highscore = score;
                            if(distance>highdistance) highdistance = distance;
                            substract();
                        }
                        reset();
                        savefile();
                        break;
                    case 2 :
                        shop();
                        savefile();
                        break;
                    case 3:
                        mission();
                        break;
                    case 4:
                        break;
                }
			}while(a!=4);
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}

