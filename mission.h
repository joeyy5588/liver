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
class LTimer
{
    public:
		//Initializes variables
		LTimer();

		//The various clock actions
		void start();
		void stop();
		void pause();
		void unpause();

		//Gets the timer's time
		Uint32 getTicks();

		//Checks the status of the timer
		bool isStarted();
		bool isPaused();
		//The clock time when the timer started
		Uint32 mStartTicks;

		//The ticks stored when the timer was paused
		Uint32 mPausedTicks;

		//The timer status
		bool mPaused;
		bool mStarted;
};

#endif
