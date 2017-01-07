#ifndef MISSION_H
#define MISSION_H
#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <sstream>
#include <iostream>
#include <SDL_ttf.h>
#include "map.h"
#include "screen.h"
#include "gButtons.h"
#include "trump.h"
#include "character.h"

bool missionloadMedia();

void missionclose();

void mission();

void add();

void substract();


#endif
