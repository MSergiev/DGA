#ifndef GAME_H
#define GAME_H

//Include SDL modules
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

//Include local modules
#include "Shared.h"
#include "Board.h"
#include "Player.h"
#include "Sound.h"
#include "Dice.h"
#include "Button.h"
#include "TitleScreen.h"
#include "WinScreen.h"
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
public:
    //Constructor
	Game();
    
    //Game loop
    void loop();
    
    //Game renderer setter
    //Args:
    //SDL_Renderer* renderer - renderer
    void setRenderer(SDL_Renderer* renderer);
    
    //SDL event container setter
    //Args:
    //SDL_Event& event - reference to event container
    void setEvent(SDL_Event& event);
	
    //Game object initializing function
    void init();

    //Event handler
    void eventHandler();

    //Render assets
    //Args:
    //bool renderDice - flag to render dice (not required)
    void render(bool renderDice = 0);

    //Destuctor
    ~Game();

private:
	
    //SDL renderer
    SDL_Renderer* mRenderer;
    
    //SDL event container
    SDL_Event mEvent;
    
    //Game state flags
    bool mbTitle = 0;
    bool mbLoop = 1;
    bool mbWin = 1;

    //Force ignore recovery
    bool mbIgnoreRecovery = 0;

    //Game font
    TTF_Font* mFont;

    //Game board
    Board mBoard;
    
    //Dice object
    Dice mDice;

    //Title screen object
    TitleScreen mTitleScreen;

    //Win screen object
    WinScreen mWinScreen;

    //Active board layout (top row leftmost square considered 1)
    Pawn* mBoardLayout[BOARD_LENGTH+10] = {NULL};
    unsigned mPawnsOnSquare[BOARD_LENGTH+10] = {0};

    //Board highlighter array
    Button mBoardHighlghters[BOARD_LENGTH+6];

    //Turn counter
    int miTurns = 0;

    //Ordered player container
    deque<Player*> mTurnOrder;

    //Deque holding finished players
    deque<Player*> mFinished;

    //Active highlighter vector
    vector<int> mActiveHighlighters;
    
    
    //Player turn
    //Args:
    //Player *p - pointer to active player
    void turn(Player *p);

    //Determine turn order
    void determineTurnOrder();

    //Roll the dice
    //Args:
    //Colors c - dice color
    int diceRoll(Colors c);

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
