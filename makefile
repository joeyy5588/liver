SDL_include="C:\SDL2\i686-w64-mingw32\include\SDL2"
SDL_lib="C:\SDL2\i686-w64-mingw32\lib"
SDL_image_include="C:\SDL2_image\i686-w64-mingw32\include\SDL2"
SDL_image_lib="C:\SDL2_image\i686-w64-mingw32\lib"
SDL_ttf_include="C:\SDL2_ttf\i686-w64-mingw32\include\SDL2"
SDL_ttf_lib="C:\SDL2_ttf\i686-w64-mingw32\lib"
SDL_mixer_include="C:\SDL2_mixer\i686-w64-mingw32\include\SDL2"
SDL_mixer_lib="C:\SDL2_mixer\i686-w64-mingw32\lib"
output=output.exe

all: main 

main: character.o game.o map.o mission.o object.o screen.o shop.o menu.o gbutton.o trump.o
	g++.exe -L $(SDL_lib) -L $(SDL_image_lib) -L $(SDL_ttf_lib) -L $(SDL_mixer_lib) -o $(output) character.o game.o map.o mission.o object.o screen.o shop.o menu.o gbutton.o trump.o -m32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer

character.o: character.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c character.cpp -o character.o

game.o: game.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I  $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c game.cpp -o game.o

map.o: map.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c map.cpp -o map.o

mission.o: mission.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c mission.cpp -o mission.o

object.o: object.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c object.cpp -o object.o

screen.o: screen.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c screen.cpp -o screen.o

shop.o: shop.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c shop.cpp -o shop.o

menu.o: menu.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c menu.cpp -o menu.o

gbutton.o: gbutton.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c gbutton.cpp -o gbutton.o

trump.o: trump.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -I $(SDL_mixer_include) -c trump.cpp -o trump.o

clear:
	cmd /c del character.o game.o map.o mission.o object.o screen.o trump.o $(output)
