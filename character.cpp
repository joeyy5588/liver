#include "character.h"
#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>

//map moving speed
int mapspeed = -3;
int asset=0;
int score=0;

Dot::Dot()
{
    //Initialize the offsets
    mPosX = 0;
    mPosY = 275;

    //Initialize the velocity
    mVelX = 1;
    mVelY = -2;

    isdown = false;
    isdead = false;
}

void Dot::handleEvent( SDL_Event& e )
{
    //If a key was pressed
	if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY -= DOT_VEL; break;
            case SDLK_DOWN: mVelY += DOT_VEL; break;
            case SDLK_LEFT: mVelX -= DOT_VEL; break;
            case SDLK_RIGHT: mVelX += DOT_VEL; break;
            case SDLK_SPACE: mVelY = -mVelY; isdown = !isdown; break;
        }
    }
    //If a key was released
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        //Adjust the velocity
        switch( e.key.keysym.sym )
        {
            case SDLK_UP: mVelY += DOT_VEL; break;
            case SDLK_DOWN: mVelY -= DOT_VEL; break;
            case SDLK_LEFT: mVelX += DOT_VEL; break;
            case SDLK_RIGHT: mVelX -= DOT_VEL; break;
        }
    }
}

void Dot::move()
{
    //Move the dot left or right
    mPosX += mVelX;

    //If the dot went too far to the left or right
    if ( mPosX > (0.5*SCREEN_WIDTH)-DOT_WIDTH )
    {
        //Move back
        mVelX = 0;
        mPosX -= mVelX;
        mapspeed = -4;
    }

    //Move the dot up or down
    mPosY += mVelY;

    //If the dot went too far up or down
    /*if( ( mPosY < 0 ) || ( mPosY + DOT_HEIGHT > SCREEN_HEIGHT ) )
    {
        //Move back
        mPosY -= mVelY;
    }*/
}

void Dot::render()
{
    //Show the dot
    if(isdown)
        gDotTexture1.render( mPosX, mPosY );
    else
        gDotTexture2.render( mPosX, mPosY );
}

bool Dot::checkborder(int &scrollingOffset)
{
    if (mPosY<(0.5*abs(((-scrollingOffset+mPosX+53)%833)-409)+73)){
        //right top
        std::cout<<mPosY<<'\t'<<(abs(((-scrollingOffset+mPosX+60)%833)-409));
        isdead = true;
        return true;
    }else if (mPosY<(0.5*abs(((-scrollingOffset+mPosX)%833)-358))+33){
        //left top
        std::cout<<mPosY<<'\t'<<(abs(((-scrollingOffset+mPosX)%833)-358));
        isdead = true;
        return true;
    }else if (mPosY+100>(768-0.5*abs(((-scrollingOffset+mPosX+53)%833)-409))){
        //right bottom
        std::cout<<mPosY+ 100<<'\t'<<(0.5*abs(((-scrollingOffset+mPosX+60)%833)-409));
        isdead = true;
        return true;
    }else if (mPosY+40>(768-0.5*abs(((-scrollingOffset+mPosX)%833)-358))){
        //left bottom
        std::cout<<mPosY+40<<'\t'<<(768-0.5*abs(((-scrollingOffset+mPosX)%833)-358)+10);
        isdead = true;
        return true;
    }else{
        return false;
    }
}
void Dot::reset()
{
    for(int i=0;i<20;i++){
        stack[i]=0;
    }
}
void Dot::checkpoint(){
    bool a,w,m;
    a=w=m=false;
    for(int i=0;i<20;i++){
        switch(stack[i]){
            case 1:
                w = true;
                break;
            case 2:
                m = true;
                break;
            case 3:
                a = true;
                break;
        }
    }
    if((a&&w)&&(!m)){
        isdead = true;
    }else if(m&&(!(a||w))){
        isdead = true;
    }

}
