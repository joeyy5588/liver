#ifndef GAME_H
#define GAME_H
#include <SDL.h>
#include <SDL_image.h>
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

int menuevent();

void normalmode();

void pausemode();

void goldmode();

void invinciblemode();

void medalmode();

void slowmode();

void reset();


#endif
