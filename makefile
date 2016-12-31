SDL_include=C:\SDL2\i686-w64-mingw32\include\SDL2
SDL_lib=C:\SDL2\i686-w64-mingw32\lib
SDL_image_include=C:\SDL2_image\i686-w64-mingw32\include\SDL2
SDL_image_lib=C:\SDL2_image\i686-w64-mingw32\lib
SDL_ttf_include=C:\SDL2_ttf\i686-w64-mingw32\include\SDL2
SDL_ttf_lib=C:\SDL2_ttf\i686-w64-mingw32\lib
output=output.exe

all: main 

main: character.o game.o map.o mission.o object.o screen.o
	g++.exe -L $(SDL_lib) -L $(SDL_image_lib) -L $(SDL_ttf_lib) -o $(output) character.o game.o map.o mission.o object.o screen.o  -m32 -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf  

character.o: character.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c character.cpp -o character.o
game.o: game.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I  $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c game.cpp -o game.o
map.o: map.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c map.cpp -o map.o

mission.o: mission.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c mission.cpp -o mission.o

object.o: object.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c object.cpp -o object.o

screen.o: screen.cpp
	g++.exe -Wall -g -m32 -std=c++11 -O2 -Wall -Wextra -I $(SDL_include) -I $(SDL_image_include) -I $(SDL_ttf_include) -c screen.cpp -o screen.o

clear:
	cmd /c del character.o game.o map.o mission.o object.o screen.o $(output)
