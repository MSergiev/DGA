test: main.cpp Recovery.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp
	g++ -o test main.cpp Recovery.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp UI.cpp TitleScreen.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpugixml -Wall
