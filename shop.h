#ifndef SHOP_H
#define SHOP_H
#include "trump.h"
#include "map.h"
#include "screen.h"
#include "gButtons.h"
void shopclose();
bool  shoploadMedia();
int shop();
class shopbutton :public LButton
{
   public:
       shopbutton();

       bool purchase ;

       void render();

       int delta;

       void handleEvent( SDL_Event* e );
};

#endif
