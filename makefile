test: main.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp
	g++ -o test main.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp Player.cpp Pawn.cpp Button.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lpugixml
