#ifndef SCREEN_H
#define SCREEN_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include "map.h"

//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

extern const int SCREEN_WIDTH ;
extern const int SCREEN_HEIGHT ;
extern LTexture gDotTexture1;
extern LTexture gDotTexture2;
extern LTexture gBGTexture;
extern LTexture gTextTexture1;
extern LTexture gTextTexture2;
extern LTexture gTextTexture3;
extern LTexture gTextTexture4;
extern LTexture gTimeTextTexture;
extern LTexture gPausePromptTexture;
extern LTexture gStartPromptTexture;
extern LTexture gMoneyTexture;
extern LTexture gBuildingTexture1;
extern LTexture gBuildingTexture2;
extern LTexture gPeopleTexture1;
extern LTexture gPeopleTexture2;
extern LTexture gPeopleTexture3;
extern LTexture gPeopleTexture12;
extern LTexture gPeopleTexture22;
extern LTexture gPeopleTexture32;

#endif
