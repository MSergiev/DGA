#ifndef GAME_H
#define GAME_H

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
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

//Misc library inclusion
#include <iostream>
using std::cerr;
using std::endl;
#include <vector>
using std::vector;
#include <deque>
using std::deque;
#include <algorithm>
using std::random_shuffle;

class Game {

private:
	
    //SDL event container
    SDL_Event mEvent;
    
    //Game state flags
    bool mbTitle = 1;
    bool mbLoop = 0;
    bool mbWin = 0;
	bool mbRules = 0;
	bool mbRoll = 0;
	bool mbHighlight = 0;

	//Dice animation timer
	Uint32 miDiceTimer = 0;

	//Current dice roll
	int miCurrentRoll = 1;

    //Force ignore recovery
    bool mbIgnoreRecovery = 0;

    //Game font
    TTF_Font* mFont;

    //Game board
    Texture mBoard;
    
    //Dice objects vector
    vector<Dice*> mDice;

    //Title screen object
    TitleScreen mTitleScreen;

    //Win screen object
    WinScreen mWinScreen;

	//Rules screen
	Info mInfoScreen;

	//UI controls object
	Controls mControls;

    //Active board layout (top row leftmost square considered 1)
    Pawn* mBoardLayout[BOARD_LENGTH+10] = {NULL};
    unsigned mPawnsOnSquare[BOARD_LENGTH+10] = {0};

    //Board highlighter array
    Button mBoardHighlghters[BOARD_LENGTH+6];

    //Active highlighter vector
    vector<int> mActiveHighlighters;

    //Turn counter
    int miTurns = 0;

    //Ordered player container
    deque<Player*> mTurnOrder;

    //Deque holding finished players
    deque<Player*> mFinished;

public:

    //Constructor
	Game();
    
    //Game loop
    void loop();
    
    //SDL event container setter
    //Args:
    //SDL_Event& event - reference to event container
    void setEvent(SDL_Event& event);
	
    //Game object initializing function
    void init();

    //Event handler
    void eventHandler();

    //Render assets
    void render();

    //Destuctor
    ~Game();
    
private:

    //Player turn
    //Args:
    //Player *p - pointer to active player
    void turn(Player *p);

    //Determine turn order
    void determineTurnOrder();

    //Roll the dice
    void diceRoll();

    //Move pawn
    //Args:
    //Pawn* p - pawn pointer
    //int from - index on board array to move it from
    //int with - amount of spaces to move it with
    void movePawn(Pawn* p, int with);

    //Collision detection
    //Args:
    //Pawn* p - pawn pointer
    //int to - index on board array to move to
    void collision(Pawn* p, int to);

    //Pawn highlighter
    //Args:
    //int index - square index to highlight
    //Colors c - color for base selection (not required)
    void highlight(int index, Colors c = NONE);

    //Highlighted squares event handler
    int getHighlightedChoice();

    //Delay
    //Args:
    //Uint32 ms - milliseconds to delay for
    void delay(Uint32 ms);
    
    //Activate pawn
    //Args:
    //Player p* - pointer to player
    void activatePawn(Player* p);

    //Get absolute from relative pawn position
    //Args:
    //Colors c - pawn color
    //int pos - relative position (not required)
    int getAbsolute(Colors c, int pos = 0);

    //Get relative from absolute board position
    //Args:
    //Colors c - pawn color
    //int pos - absolute position (not required)
    int getRelative(Colors c, int pos = 0);
    
    //Get screen coordinates from pawn position
    //Args:
    //Colors c - pawn color
    //int p - pawn position
    pair<int, int> getCoords(Colors c, int p);

};

#endif
