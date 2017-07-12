test: main.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp
	g++ -o test main.cpp Texture.cpp Sprite.cpp Board.cpp Sound.cpp Dice.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lpugixml
