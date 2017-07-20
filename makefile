test: main.cpp Game.cpp Recovery.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp WinScreen.cpp
	g++ -o test main.cpp Game.cpp Recovery.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp WinScreen.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpugixml -Wall
