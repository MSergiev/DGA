#ifndef GAME_H
#define GAME_H

///Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

///Include local modules
#include "Shared.h"
#include "Player.h"
#include "Sound.h"
#include "Dice.h"
#include "Button.h"
#include "TitleScreen.h"
#include "WinScreen.h"
#include "Info.h"
#include "Controls.h"
#include "Recovery.h"

///Misc library inclusion
#include <iostream>
using std::cerr;
using std::endl;
#include <vector>
using std::vector;
#include <deque>
using std::deque;
#include <algorithm>
using std::random_shuffle;

//Game screen enum
enum Screens{
	BLANK=0, RULES1, RULES2, TITLE, GAME, WIN
};

class Game {

private:
	
    ///SDL event container
    SDL_Event mEvent;

	///Camera coordinates
	int miCameraX;
	int miCameraY;

    ///Game state flags
	bool mbRunning;
	bool mbRoll;
	bool mbMove;
	bool mbTransition;
	bool mbHighlight;

	///Transition data
	int miOldTransitionX, miOldTransitionY;
	int miCurrentDistance, miDestinationDistance;
	pair<float,float> mDirection;
	Uint32 miTransitionTimer;

	///Move remaining moves
	int miRemaining;

	///Movement pawn data
	Pawn* mMovingPawn;

	///Movement delay timer
	Uint32 miMoveDelay;

	///Dice animation timer
	Uint32 miDiceTimer;

    ///Force ignore recovery
    bool mbIgnoreRecovery;

    ///Game font
    TTF_Font* mFont;

    ///Game board
    Texture mBoard;
    
    ///Dice objects array
	vector<Dice*> mDice;

    ///Title screen object
    TitleScreen mTitleScreen;

    ///Win screen object
    WinScreen mWinScreen;

	///Rules screen
	Info mInfoScreen;

	///Active UI pointer
	UI* mActiveUI;

	///UI controls object
	Controls mControls;

    ///Active board layout (top row leftmost square considered 0)
	vector<Pawn*> mBoardVector[BOARD_HEIGHT][BOARD_WIDTH];

    ///Board highlighter array
    Button mBoardHighlghters[BOARD_HEIGHT][BOARD_WIDTH];

    ///Active highlighter index vector
    vector<pair<int,int> > mActiveHighlighters;

    ///Ordered player container
    deque<Player*> mTurnOrder;

	//Current screen
	Screens meScreen;

	///Explosion FX data
	Sprite mExplosion;
	bool mbExplosion;
	pair<int,int> mExplosionCoords;

	///Shockwave FX data
	Sprite mShockwave;
	bool mbShockwave;
	pair<int,int> mShockwaveCoords;


public:

    ///Constructor
	Game();
    
    ///Game loop
    void loop();
    
    ///SDL event container setter
    ///Args:
    ///SDL_Event& event - reference to event container
    void setEvent(SDL_Event& event);
	
    ///Game object initializing function
    void init();
   
   	///Game data initializing function
    void initGame();

    ///Event handler
    void eventHandler();

    ///Render assets
    void render();

    ///Destuctor
    ~Game();
    
private:
	
	///Render background
	void renderBackground();

	///Render sprite layer
	void renderSprite();

	///Render UI
	void renderUI();
    
	///Screen transition method
	///Args:
	///Screens to - screen to transition to (not required)
	///bool instant - instant transition (not required)
	void transition(Screens to = BLANK, bool instant = 0);

	///Player turn
    ///Args:
    ///Player *p - pointer to active player
    void turn(Player *p);

    ///Determine turn order
    void determineTurnOrder();

    ///Roll the dice
    void diceRoll();

    ///Move pawn
    ///Args:
    ///Pawn* p - pawn pointer
    ///int from - index on board array to move it from
    ///int with - amount of spaces to move it with
    void movePawn(Pawn* p, int with);

    ///Collision detection
    ///Args:
    ///Pawn* p - pawn pointer
    ///int pX - destination X index
	///int pY - destination Y index
    void collision(Pawn* p, int pX, int pY);

    ///Board square highlighter
    ///Args:
    ///int pX - X coordinate index
	///int pY - Y coordinate index
    void highlight(int pX, int pY);

    ///Highlighted squares event handler
    pair<int,int> getHighlightedChoice();

    ///Delay
    ///Args:
    ///Uint32 ms - milliseconds to delay for
    void delay(Uint32 ms);
    
    ///Activate pawn
    ///Args:
    ///Player p* - pointer to player
    void activatePawn(Player* p);

    ///Get screen coordinates from board position
    ///Args:
    ///int pX - X index
	///int pY - Y index
    pair<int,int> getCoords(int pX, int pY);

    ///Get screen coordinates for final position
    ///Args:
    ///Color c - player color
	///int pos - position in final vector
    pair<int,int> getFinalCoords(Colors c, int pos);
	
	///Determine if board square is active
	///Args:
	///int pX - X index
	///int pY - Y index
	bool isActive(int pX, int pY);

	///Determine if board square is safe
	///Args:
	///int pX - X index
	///int pY - Y index
	///Colors c - player color
	bool isSafe(int pX, int pY, Colors c);
	
	///Determine if board square is active
	///Args:
	///int pX - X index
	///int pY - Y index
	///Colors c - player color
	bool isFinal(int pX, int pY, Colors c);
	
	///Determine if board square is base
	///Args:
	///int pX - X index
	///int pY - Y index
	///Colors c - player color
	bool isBase(int pX, int pY, Colors c);	

	///Determine if board square is entry
	///Args:
	///int pX - X index
	///int pY - Y index
	///Colors c - player color
	bool isEntry(int pX, int pY, Colors c);

	///Determine if player has finished
	///Args:
	///Player* p - pointer to player
	bool hasFinished(Player* p);

	///Active UI switcher
	void switchUI();
};

#endif
