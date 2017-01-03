#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <iostream>
#include <SDL_ttf.h>
#include "character.h"
#include "screen.h"
#include "mission.h"
#include "object.h"
#include "menu.h"
#include "gButtons.h"
#include "trump.h"
#include "shop.h"
//#include "shop.h"

int menuevent();

void normalmode();

void pausemode();

void reset();


#endif
