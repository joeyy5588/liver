#include "character.h"
#include "screen.h"
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <sstream>
#include <SDL_ttf.h>
#include <cmath>

//map moving speed
int mapspeed = -3;
int asset=0;
int score=0;
int distance = 0;
int triggeredtime = 0;
bool triggered = false;
std::stringstream abilitytext;
LTexture abtext;

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
            case SDLK_SPACE: mVelY = -mVelY; isdown = !isdown; break;
        }
    }
}

void Dot::move()
{
    //Move the dot left or right
    /*mVelX = mapspeed+4;
    if(mVelX<0) mVelX = 0;
    mVelY = 0.5*(mapspeed-mVelX);*/


    //If the dot went too far to the left or right
    if ( mPosX > (0.5*SCREEN_WIDTH)-DOT_WIDTH &&mapspeed!=-2&&mapspeed!=-6)
    {
        //Move back
        mVelX = 0;
        mPosX -= mVelX;
        mapspeed = -4;
    }
    if(mapspeed==-2){
       if(mVelY>0) mVelY =1;
       if(mVelY<0) mVelY =-1;
    }
    if(mapspeed==-6){
        mVelX = 0;
        if(mVelY>0) mVelY =3;
        if(mVelY<0) mVelY =-3;
    }
    mPosX += mVelX;
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
        //std::cout<<mPosY<<'\t'<<(abs(((-scrollingOffset+mPosX+60)%833)-409));
        isdead = true;
        return true;
    }else if (mPosY<(0.5*abs(((-scrollingOffset+mPosX)%833)-358))+33){
        //left top
        //std::cout<<mPosY<<'\t'<<(abs(((-scrollingOffset+mPosX)%833)-358));
        isdead = true;
        return true;
    }else if (mPosY+100>(768-0.5*abs(((-scrollingOffset+mPosX+53)%833)-409))){
        //right bottom
        //std::cout<<mPosY+ 100<<'\t'<<(0.5*abs(((-scrollingOffset+mPosX+60)%833)-409));
        isdead = true;
        return true;
    }else if (mPosY+40>(768-0.5*abs(((-scrollingOffset+mPosX)%833)-358))){
        //left bottom
        //std::cout<<mPosY+40<<'\t'<<(768-0.5*abs(((-scrollingOffset+mPosX)%833)-358)+10);
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
void Dot::mapevent(int time)
{
    static int curr ;
    static int endp ;
    if(!triggered){
        curr = endp = 0;
    }
    static int ab;
    bool activated = false;
    abilitytext.str("");
    if(triggered){
        std::cout<<"triggered"<<std::endl;
        if(time==0){
            while(activated==false){
                ab = rand()%4;
                switch(ab){
                    case 0 :
                        if(billionaire==true){
                            activated=true;
                        }
                        break;
                    case 1 :
                        if(timemachine==true){
                            activated=true;
                        }
                        break;
                    case 2 :
                        if(champion==true){
                            activated=true;
                        }
                        break;
                    case 3 :
                        if(superman==true){
                            activated=true;
                        }
                        break;

                }
            }
        }
        switch(ab){
            case 0:
                if(curr==0) curr = asset;
                abilitytext<<"Billionaire";
                if( !abtext.loadFromRenderedText( abilitytext.str().c_str(), { 49, 49, 49 } ) )
                {
                    printf( "Unable to render time texture!\n" );
                }
                abtext.render(0,80);
                if(time>20000){
                    endp=asset;
                    asset+=(endp-curr);
                    curr = endp = 0;
                    time = 0;
                    activated = triggered = false;
                }
                break;
            case 1:
                mapspeed = -2;
                abilitytext<<"Time Machine";
                if( !abtext.loadFromRenderedText( abilitytext.str().c_str(), { 49, 49, 49 } ) )
                {
                    printf( "Unable to render time texture!\n" );
                }
                abtext.render(0,80);
                if(time>10000){
                    mapspeed = -4;
                    if(mVelY>0) mVelY =2;
                    if(mVelY<0) mVelY =-2;
                    curr = endp = 0;
                    time = 0;
                    activated = triggered = false;
                }
                break;
            case 2:
                if(curr==0) curr = score;
                abilitytext<<"Champion";
                if( !abtext.loadFromRenderedText( abilitytext.str().c_str(), { 49, 49, 49 } ) )
                {
                    printf( "Unable to render time texture!\n" );
                }
                abtext.render(0,80);
                if(time>20000){
                    endp=score;
                    score+=(endp-curr);
                    time = curr = endp = 0;
                    activated = triggered = false;
                }
                break;
            case 3:
                abilitytext<<"Superman";
                if( !abtext.loadFromRenderedText( abilitytext.str().c_str(), { 49, 49, 49 } ) )
                {
                    printf( "Unable to render time texture!\n" );
                }
                isdead = false;
                abtext.render(0,80);
                if(time>20000){
                    time = curr = endp = 0;
                    activated = triggered = false;
                }
                break;

        }
    }
}
void Dot::checkpoint(){
    Mix_PlayChannel( -1, gplus, 0 );
    bool a,w,m;
    a=w=m=false;
    int ac,wc,mc,conti,total,temp;
    ac=wc=mc=conti=total=temp=0;
    for(int i=0;i<20;i++){
        if(stack[i]==temp&&stack[i]!=0){
            conti++;
        }else{
            if(conti>=3){
                score+=(conti-2);
                asset+=(conti-2);
            }
            conti=1;
        }
        switch(stack[i]){
            case 1:
                w = true;
                total++;
                wc++;
                break;
            case 2:
                m = true;
                total++;
                mc++;
                break;
            case 3:
                a = true;
                total++;
                ac++;
                break;
            default:
                break;
        }
        temp = stack[i];
    }
    if((a&&w)&&(!m)){
        isdead = true;
    }else if(m&&(!(a||w))){
        isdead = true;
        if(mc>=3){
            score-=(mc-2);
        }
    }else if (ac==mc&&mc==wc&&wc==ac){
        score+=total;
        score+=10;
        asset+=10;
    }
    else{
        score+=total;
    }
}
