#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <string>
#include "level.h"
#include "board.h"
#include "window.h"
class Game {
	Level *lv;std::string stringLv;//level and the level string buffer
	Board *b; //board
	bool display; //1 is open the display ... 0 is not open
	Xwindow * xWin;
	std::string inF;
	int score;std::string sscore; //score and score string buffer
	int hiScore;std::string shiScore; //hi score and hi score string buffer
public:
	Game(Xwindow *w);
	Game(int s,int n,Xwindow *w,std::string inF,bool g);
	~Game();
	int levelOut();
	void controlLv(bool n); // 1 to go up,0 to go down
	void endGame();
	void runGame(std::string s);
	void header(); //print the header of the game
	void body();
	void startGame(bool d); //start a new game
	void restart();
};


#endif /* GAME_H_ */
