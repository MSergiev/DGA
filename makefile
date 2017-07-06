test: main.cpp Texture.cpp Sprite.cpp Board.cpp Player.cpp
	g++ -o test main.cpp Texture.cpp Sprite.cpp Board.cpp Player.cpp -lSDL2 -lSDL2_image -lSDL2_mixer
