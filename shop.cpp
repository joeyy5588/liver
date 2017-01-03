#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mouse.h>
#include <stdio.h>
#include <string>
#include <cstdlib>
#include "shop.h"
#include "trump.h"
using namespace std;


 shopbutton::shopbutton()
 {
     LButton();
     purchase=false;
     delta=0;
 }


void shopbutton::render()
{  SDL_Rect temp;
    temp.x= mPosition.x;
    temp.y=mPosition.y;
    temp.h=BUTTON_HEIGHT;
    temp.w=BUTTON_WIDTH;
    mCurrentsurface.render( mPosition.x, mPosition.y+delta, &temp );

}


  void shopbutton::handleEvent( SDL_Event* e )
  {
    if( e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN/*|| e->type == SDL_MOUSEWHEEL_NORMAL||e->type==SDL_MOUSEWHEEL_FLIPPED*/ )
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
		else if( y < mPosition.y+delta )
		{
			inside = false;
		}
		//Mouse below the button
		else if( y > mPosition.y + BUTTON_HEIGHT+delta )
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




LTexture finalscene;
LTexture buttondown;
LTexture buttonup;
LTexture buydont;
LTexture buydefault;
LTexture shopdefault[3];
LButton buy[2];
shopbutton option[8];
shopbutton home;
shopbutton click[2];
bool  shoploadMedia()
{

    buttondown.loadFromFile("pic/buttondown.png");
    buttonup.loadFromFile("pic/buttonup.png");
    finalscene.loadFromFile("pic/final.png");
	//Loading success flag
	bool success = true;

	buydont.loadFromFile("pic/buydont.png");
	//Load default surface
    buydefault.loadFromFile( "pic/buyask.png" );
	if( !buydefault.loadFromFile( "pic/buyask.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	shopdefault[0].loadFromFile( "pic/shop.png"  );
	if( !shopdefault[0].loadFromFile( "pic/shop.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	shopdefault[1].loadFromFile( "pic/shop1.png"  );
	if( !shopdefault[1].loadFromFile( "pic/shop1.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}

	shopdefault[2].loadFromFile( "pic/shop2.png"  );
	if( !shopdefault[2].loadFromFile( "pic/shop2.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	buy[0].mCurrentsurface.loadFromFile( "pic/buyyes.png" );
	if( !buy[0].mCurrentsurface.loadFromFile( "pic/buyyes.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
	buy[1].mCurrentsurface.loadFromFile( "pic/buyno.png" );
	if( !buy[1].mCurrentsurface.loadFromFile( "pic/buyno.png" ) )
	{
		printf( "Failed to load default image!\n" );
		success = false;
	}
    click[0].setPosition(450,680);
    click[1].setPosition(450,0);
    click[0].BUTTON_HEIGHT = 82;
    click[0].BUTTON_WIDTH = 144;
    click[1].BUTTON_HEIGHT = 82;
    click[1].BUTTON_WIDTH = 144;
	buy[1].BUTTON_HEIGHT = 550-477;
    buy[1].BUTTON_WIDTH = 756-554;
    buy[0].BUTTON_HEIGHT = 550-477;
    buy[0].BUTTON_WIDTH = 470-271;
    buy[0].setPosition(271,477);
    buy[1].setPosition(554,477);
    home.setPosition(892,25);
    home.BUTTON_HEIGHT = 118-25;
    home.BUTTON_WIDTH = 973-892;
    for(int i=0;i<8;i++)
    {
        option[i].BUTTON_HEIGHT=270;
        option[i].BUTTON_WIDTH=81;
    }

    option[0].setPosition(892,177);
    option[1].setPosition(892,482);
    option[2].setPosition(892,784);
    option[3].setPosition(892,1092);
    option[4].setPosition(892,1392);
    option[5].setPosition(892,1701);
    option[6].setPosition(892,2007);
    option[7].setPosition(892,2318);
    if(billionaire) option[0].purchase = true;
    if(timemachine) option[1].purchase = true;
    if(champion) option[2].purchase = true;
    if(superman) option[3].purchase = true;
    if(puzzle1) option[4].purchase = true;
    if(puzzle2) option[5].purchase = true;
    if(puzzle3) option[6].purchase = true;
    if(puzzle4) option[7].purchase = true;

	return success;
}

void shopclose()
{
	//Deallocate surfaces
	for( int i = 0; i < 8; ++i )
	{
		 option[ i ].mCurrentsurface.free();

	}
    for( int i = 0; i < 2; ++i )
	{
		 buy[i].mCurrentsurface.free();

	}
	for( int i = 0; i < 2; ++i )
	{
		 click[i].mCurrentsurface.free();

	}
	 for( int i = 0; i < 3; ++i )
	{
		 shopdefault[i].free();

	}
	 buydefault.free();

	 home.mCurrentsurface.free();
     buydont.free();


}





int shop()
{


		//Load media
		if( !shoploadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

            start:
            int screendelta=0;
            shopdefault[0].render(0,screendelta);

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
					   SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                       SDL_RenderClear( gRenderer );
					  shopdefault[0].render(0,screendelta);

                    if(screendelta!=0) buttonup.render(450,0);
                    if(screendelta!=-1869)buttondown.render(450,680);


                       home.handleEvent(&e ); if(home.show==true)  home.render();
                      click[0].handleEvent(&e) ; if (click[0].press==true)  {click[0].press=false;screendelta-=623;if(screendelta<-623*3)screendelta=-623*3;}
                      click[1].handleEvent(&e) ; if (click[1].press==true)  {click[1].press=false;screendelta+=623;if(screendelta>0)screendelta=0;}

            for( int i = 0; i <8; ++i )
            {
              {option[ i ].delta=screendelta;}
            }
             home.delta=screendelta;

             for( int i = 0; i <8; ++i )
            {
              {option[ i ].delta=screendelta;}
            }
             home.delta=screendelta;

					//Handle button events
            for( int i = 0; i < 8; ++i )
            {
                option[ i ].handleEvent(&e );
            }

            home.handleEvent(&e);
            if(home.show==true)  {home.mCurrentsurface=shopdefault[1];}
            else   {home.mCurrentsurface=shopdefault[0];}


            for(int j=0;j<8;j++)
            {
             if(option[j].purchase==true){option[j].mCurrentsurface=shopdefault[2];}
             else {
                    if(option[j].show==true)  {option[j].mCurrentsurface=shopdefault[1];}
                    else   {option[j].mCurrentsurface=shopdefault[0];}
                  }
            }


             for( int i = 0; i <8; ++i )
            { if(option[i].show==true)
              {option[ i ].render();}
            }

             for( int i = 0; i <8; ++i )
            { if(option[i].purchase==true)
              {option[ i ].render();}
            }

			for( int i = 0; i < 8; ++i )
			{if(option[i].press==true)
              {  option[i].press=false; int ability=i;

                 bool torender = false;
                 if((i>=0)&&(i<=4)){
                    if(totalmoney<250) torender = true;
                 }
                 if(i==5){
                    if(totalmoney<500) torender = true;
                 }
                 if(i==6){
                    if(totalmoney<750) torender = true;
                 }
                 if(i==7){
                    if(totalmoney<1000) torender = true;
                 }
                 if(torender)
                 {
                     SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                     SDL_RenderClear( gRenderer );
                     buydont.render(0,0);
                     SDL_RenderPresent( gRenderer );
                     SDL_Delay(2000);
                     std::cout<<totalmoney<<" "<<i<<std::endl;
                     goto start;
                 }



                 while( !quit )
                 {while( SDL_PollEvent( &e ) != 0 )
                  {for( int i = 0; i < 2; ++i )
					  {
						buy[ i ].handleEvent( &e );
					  }
                   buydefault.render(0,0);
                   for( int i = 0; i <2; ++i )
                  { if(buy[i].show==true)
                  {buy[i].show=false;buy[ i ].render();}
                  }

                SDL_RenderPresent( gRenderer );

                if(buy[0].press==true)
                {
                  buy[0].press=false;
                  option[ability].purchase=true;
                  if(ability==0) {totalmoney-=250;billionaire=true;}
                  else if(ability==1) {totalmoney-=250;timemachine=true;}
                  else if(ability==2) {totalmoney-=250;champion=true;}
                  else if(ability==3) {totalmoney-=250;superman=true;}
                  else if(ability==4) {totalmoney-=250;puzzle1=true;}
                  else if(ability==5) {totalmoney-=500; puzzle2=true;}
                  else if(ability==6) {totalmoney-=750; puzzle3=true;}
                  else if(ability==7) {totalmoney-=1000;puzzle4=true;}
                  if(!(puzzle1&&puzzle2&&puzzle3&&puzzle4))goto start;
                }
                if(puzzle1&&puzzle2&&puzzle3&&puzzle4){
                    finalscene.render(0,0);
                    SDL_RenderPresent( gRenderer );
                    SDL_Delay(2000);
                    system("start http://45gsp.blogspot.tw/2016/12/SP2010.html");
                    quit = true;
                    break;
                }
                 }
                if(buy[1].press==true) {buy[1].press=false; goto  start;}
              }}}


            if(home.press==true) { home.press=false;goto close;}





				SDL_RenderPresent( gRenderer );

				//Update the surface

			}
		  }
      }

  close:
	shopclose();

	return 0;
}
