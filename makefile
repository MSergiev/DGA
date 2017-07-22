test: main.cpp Game.cpp Recovery.cpp Texture.cpp Sprite.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp WinScreen.cpp Info.cpp
	g++ -o test main.cpp Game.cpp Recovery.cpp Texture.cpp Sprite.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp WinScreen.cpp Info.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpugixml -Wall
