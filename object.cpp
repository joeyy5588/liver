#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include <cmath>
#include "object.h"

void mapobject::arrayinit(int x, int y, int z, int i)
{
    m = x;
    o = y;
    p = z;
    mapcount = i;
}
void mapobject::reset()
{
    for(int i=0; i<m; i++){
        mapmoney[i] = money();
        mapmoney[i].isvalid = rand()%2;
        int cx=0,cy=0;
        do
        {
            cx = rand()%5;
            cy = rand()%4;
        }while(checkobjectrepeat(cx, cy));
        objectpositionx[i]=cx;
        objectpositiony[i]=cy;
        objecttype[i]=1;
        mapmoney[i].mPosX = 15 + cx*106 + cy*106 + mapcount*840;
        mapmoney[i].mPosY = 384 + cx*61 - cy*61;
    }
    for(int i=0; i<o; i++){
        mapobstacle[i] = obstacle();
        mapobstacle[i].isvalid = rand()%2;
        int cx=0,cy=0;
        do
        {
            cx = rand()%5;
            cy = rand()%4;
        }while(checkobjectrepeat(cx, cy));
        objectpositionx[m+i]=cx;
        objectpositiony[m+i]=cy;
        if(mapobstacle->buildingtype==0){
            objecttype[m+i]=2;
            mapobstacle[i].mPosX = -30 + cx*108 + cy*108 + mapcount*840;
            mapobstacle[i].mPosY = 155 + cx*61 - cy*61;
        }else{
            objecttype[m+i]=2;
            mapobstacle[i].mPosX = 7 + cx*106 + cy*106 + mapcount*840;
            mapobstacle[i].mPosY = 228 + cx*63 - cy*63;
        }
    }
    for(int i=0; i<p; i++){
        mappeople[i] = people();
        mappeople[i].isvalid = rand()%2;
        int cx=0,cy=0;
        do
        {
            cx = rand()%5;
            cy = rand()%4;
        }while(checkobjectrepeat(cx, cy));
        objectpositionx[m+o+i]=cx;
        objectpositiony[m+o+i]=cy;
        objecttype[m+o+i]=3;
        mappeople[i].mPosX = cx*106 + cy*106 + mapcount*840;
        mappeople[i].mPosY = 348 + cx*69 - cy*69;
    }
}
bool mapobject::checkobjectrepeat(int x, int y)
{
    for(int i=0;i<20;i++){
        if((objectpositionx[i]==x)&&(objectpositiony[i]==y)){
            return true;
        }
    }
    return false;
}
void money::move(int &scrollingOffset)
{
    mVelX = scrollingOffset;
    mPosX += mVelX;
}
void money::render()
{
    //Show the dot
    if(isvalid)
        gMoneyTexture.render( mPosX, mPosY );
}
void money::checkcollision(Dot &T)
{
    if(T.isdown){
        if((abs(mPosX-T.mPosX)<69)&&(mPosX>T.mPosX)&&(abs(mPosY-T.mPosY)<64)){
            isvalid = 0;
            asset++;
        }
    }else{
        if((abs(mPosX-T.mPosX)<69)&&(mPosX>T.mPosX)&&(abs(mPosY-T.mPosY)<50)){
            isvalid = 0;
            asset++;
        }
    }
}
/*obstacle::obstacle()
{
    isvalid = mVelX = mVelY = mPosX = mPosY = 0;
    buildingtype = rand()%2;
}*/
void obstacle::move(int &scrollingOffset)
{
    mVelX = scrollingOffset;
    mPosX += mVelX;
}
void obstacle::render()
{
    //Show the dot
    if(isvalid&&buildingtype)
        gBuildingTexture2.render( mPosX, mPosY );
    else if (isvalid)
        gBuildingTexture1.render( mPosX, mPosY );
}
void obstacle::checkcollision(Dot &T)
{
    if(buildingtype==0){
        if(T.isdown){
            if((abs(mPosX-T.mPosX)<53)&&(mPosX>T.mPosX)&&((T.mPosY-mPosY)>160)&&((T.mPosY-mPosY)<237)){
                T.isdead=true;
            }
        }else{
            if((abs(mPosX-T.mPosX)<39)&&(mPosX>T.mPosX)&&((T.mPosY-mPosY)>220)&&((T.mPosY-mPosY)<260)){
                T.isdead=true;
            }
        }
    }
    if(buildingtype==1){
        if(T.isdown){
            if((abs(mPosX-T.mPosX)<53)&&(mPosX>T.mPosX)&&((T.mPosY-mPosY)>102)&&((T.mPosY-mPosY)<163)){
                T.isdead=true;
            }
        }else{
            if((abs(mPosX-T.mPosX)<60)&&(mPosX>T.mPosX)&&((T.mPosY-mPosY)>121)&&((T.mPosY-mPosY)<187)){
                T.isdead=true;
            }
        }
    }
}
/*people::people()
{
    isvalid = mVelX = mVelY = mPosX = mPosY = 0;
    peopletype = rand()%3;
}*/
void people::move(int &scrollingOffset)
{
    mVelX = scrollingOffset;
    mPosX += mVelX;
}
void people::render(Dot& T)
{
    //Show the dot
    if(append){
        if(T.isdown){
            if (peopletype==1)
                gPeopleTexture1.render( mPosX, mPosY);
            else if (peopletype==2)
                gPeopleTexture2.render( mPosX, mPosY);
            else if (peopletype==3)
                gPeopleTexture3.render( mPosX, mPosY);
        }else{
            if (peopletype==1)
                gPeopleTexture12.render( mPosX, mPosY);
            else if (peopletype==2)
                gPeopleTexture22.render( mPosX, mPosY);
            else if (peopletype==3)
                gPeopleTexture32.render( mPosX, mPosY);
        }
    }else{
        if(isvalid&&peopletype==1)
            gPeopleTexture1.render( mPosX, mPosY );
        else if (isvalid&&peopletype==2)
            gPeopleTexture2.render( mPosX, mPosY );
        else if (isvalid&&peopletype==3)
            gPeopleTexture3.render( mPosX, mPosY );
    }

}
void people::checkcollision(Dot &T)
{
    if(T.isdown){
        if((abs(mPosX-T.mPosX)<53)&&(mPosX>T.mPosX)&&(abs(mPosY-T.mPosY)<60)){
            int i=0;
            for(i;T.stack[i]!=0;i++){}
            T.stack[i] = peopletype;
            apporder = i+1;
            mPosX=T.mPosX;
            mPosY=T.mPosY-65*(i+1);
            mVelX=T.mVelX;
            mVelY=T.mVelY;
            append = true;
        }
    }else{
        if((abs(mPosX-T.mPosX)<69)&&(mPosX>T.mPosX)&&(abs(mPosY-T.mPosY)<60)){
            int i=0;
            for(i;T.stack[i]!=0;i++){}
            T.stack[i] = peopletype;
            apporder = i+1;
            mPosX=T.mPosX;
            mPosY=T.mPosY-65*(i+1);
            mVelX=T.mVelX;
            mVelY=T.mVelY;
            append = true;
        }
    }
}
void mapobject::move(int &scrollingOffset)
{
     for(int i=0; i<m; i++){
        if(mapmoney[i].isvalid){
                mapmoney[i].move(scrollingOffset);
        }
     }
     for(int i=0; i<o; i++){
        if(mapobstacle[i].isvalid){
                mapobstacle[i].move(scrollingOffset);
        }
     }
     for(int i=0; i<p; i++){
        if(mappeople[i].isvalid){
                mappeople[i].move(scrollingOffset);
        }
     }
}
void mapobject::render(Dot& T)
{
    for(int k=-3;k<=4;k++){
        for(int i=0;i<20;i++){
            if(objectpositionx[i]-objectpositiony[i]==k){
                switch(objecttype[i]){
                    case 1:
                        mapmoney[i].render();
                        break;
                    case 2:
                        mapobstacle[i-m].render();
                        break;
                    case 3:
                        mappeople[i-m-o].render(T);
                        break;
                }
            }
        }
    }
}
void mapobject::renderstack(Dot& T)
{
    for(int j=0;j<20;j++){
        for(int i=0;i<20;i++){
            if((mappeople[i].apporder==j)&&(mappeople[i].append))
                mappeople[i].render(T);
        }
    }
}
void mapobject::checkcollision(Dot &T)
{
    for(int i=0; i<m; i++){
        if(mapmoney[i].isvalid){
            mapmoney[i].checkcollision(T);
        }
     }
     for(int i=0; i<o; i++){
        if(mapobstacle[i].isvalid){
            mapobstacle[i].checkcollision(T);
        }
     }
     for(int i=0; i<p; i++){
        if(mappeople[i].isvalid){
            mappeople[i].checkcollision(T);
        }
     }
}
void mapobject::appmove(Dot& T)
{
    for(int i=0; i<p; i++){
        if(mappeople[i].append){
                mappeople[i].mPosX = T.mPosX;
                mappeople[i].mPosY = (T.mPosY-mappeople[i].apporder*65);
        }
     }
}
