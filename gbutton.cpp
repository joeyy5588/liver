#include "Gbuttons.h"

#include <iostream>



LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
    show=false;
   press=false;

}
void LButton::setPosition( int x, int y )
{
	mPosition.x = x;
	mPosition.y = y;
}
void LButton::handleEvent( SDL_Event* e )
{
	//If mouse event happened
	if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP )
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState( &x, &y );

		//Check if mouse is in button
		bool inside = true;

		//Mouse is left of the button
		if( x < mPosition.x )
		{
			inside = false;
		}
		//Mouse is right of the button
		else if( x > mPosition.x + BUTTON_WIDTH )
		{
			inside = false;
		}
		//Mouse above the button
		else if( y < mPosition.y )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT )
		{
			inside = false;
		}

		//Mouse is outside button
		if( !inside )
		{
			show=false;//mCurrentSprite = BUTTON_SPRITE_DEFAULT;
		}
		//Mouse is inside button
		else
		{
			//Set mouse over sprite
			switch( e->type )
			{
				case SDL_MOUSEMOTION:
				 show=true;
				break;

				case SDL_MOUSEBUTTONDOWN:
				 press=true;
				break;


			}
		}
	}
}
void LButton::render()
{

    mCurrentsurface.render(0,0);
}

