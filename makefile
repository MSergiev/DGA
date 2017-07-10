test: main.cpp Texture.cpp Sprite.cpp Board.cpp Player.cpp Recovery.cpp Sound.cpp
	g++ -o test main.cpp Texture.cpp Sprite.cpp Board.cpp Player.cpp Recovery.cpp Sound.cpp -lSDL2 -lSDL2_image -lSDL2_mixer -lpugixml
