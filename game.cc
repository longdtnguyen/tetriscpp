#include <iomanip>
#include "game.h"
#include <sstream>
#include <locale>
#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

Game::Game(Xwindow * xw):score(0) {
	hiScore =0;
	display = 11;
	lv = new Level(0,-1,inF);
	b = new Board(xw,display);
	xWin = xw;
}

Game::Game(int s,int n,Xwindow* xw,string inF,bool thed):score(0) {
	hiScore = 0;
	display = thed;	
	lv = new Level(n,s,inF);
	b = new Board(xw,display);
	xWin = xw;
}

Game::~Game() {
	delete lv;
	delete b;
}
int Game::levelOut() {
	return lv->getLv();
}
void Game::startGame(bool dp) {
	display = dp;
	char buffer = lv->create();
	b->firstBlock(buffer);	
	if(display) {
		stringLv = static_cast<ostringstream*>( &(ostringstream() << lv->getLv()) )->str();
		xWin->drawBigString(260,30,"Level: ",1);
		xWin->drawBigString(430,30,stringLv,1);
		sscore = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
		xWin->drawBigString(260,60,"Score: ",1);
		xWin->drawBigString(430,60,sscore,1);

		shiScore = static_cast<ostringstream*>( &(ostringstream() << hiScore) )->str();
		xWin->drawBigString(260,90,"Hi Score: ",1);
		xWin->drawBigString(430,90,shiScore,1);
	}
}

void Game::runGame(string s) {
	//move down
	if (s == "down"){
		int temp = b->currentX();
		b->moveBlock('D');
		if(temp == b->currentX())s = "drop";
	}
	//drop block
	if (s == "drop") {
		if(display) {
			xWin->drawBigString(430,60,sscore,0);
			xWin->drawBigString(430,90,shiScore,0);
			xWin->drawBigString(430,30,stringLv,0);
		}
		b->dropBlock();
		int old = score;
		int rows = b->clearRow();
		if(rows > 0) score += pow(rows + lv->getLv(),2);
		if (score > old){
			if (lv->getLv() < 1 && score >= 10)lv->levelUp();
			else if (lv->getLv() < 2 && score >=20)lv->levelUp();
			else if (lv->getLv() < 3 && score >=40)lv->levelUp();
			else if (lv->getLv() < 4 && score >= 70)lv->levelUp();
			score += b->clearEmpty();
			if(score > hiScore)hiScore= score;
			//check for empty blocks
		}
		
		char buffer = lv->create();
		b->nextBlock(buffer, lv->getLv());
		if(display) {
			stringLv = static_cast<ostringstream*>( &(ostringstream() << lv->getLv()) )->str();
			xWin->drawBigString(430,30,stringLv,1);
			sscore = static_cast<ostringstream*>( &(ostringstream() << score) )->str();
			xWin->drawBigString(430,60,sscore,1);
			shiScore = static_cast<ostringstream*>( &(ostringstream() << hiScore) )->str();
			xWin->drawBigString(430,90,shiScore,1);
		}
		//checking if is over
		if(b->isOver()){
			string endG; //buffer for end game
			if(display) {
				xWin->fillRectangle(0,76,250,375,0);
				xWin->drawBigString(50,130,"Game Over",2);
				xWin->drawBigString(50,170,"\"New Game\"(n)",2);
				xWin->drawBigString(50,210,"\"Quit\"(q)",2);
			}

			cout << "enter \"New Game\"(n) or \"quit\"(q)" << endl;
			while(cin>>endG) {
				if(endG[0] == 'n') {
					if(display) xWin->fillRectangle(0,76,250,375,0);
					restart();
					cout <<"Game has been restarted" << endl;
					break;
				}else if(endG[0] == 'q') {
					exit(1);
				}else  cout << "enter \"New Game\"(n) or \"quit\"(q)" << endl;
			}
		}
	}
	else if (s == "rotate") b->rotateBlock('c');
	else if (s == "crotate") b->rotateBlock('a');
	else if (s == "levelup") {
		xWin->drawBigString(430,30,stringLv,0);
		lv->levelUp();
		stringLv = static_cast<ostringstream*>( &(ostringstream() << lv->getLv()) )->str();
		xWin->drawBigString(430,30,stringLv,1);
	}else if (s == "leveldown") {
		xWin->drawBigString(430,30,stringLv,0);
		lv->levelDown();
		stringLv = static_cast<ostringstream*>( &(ostringstream() << lv->getLv()) )->str();
		xWin->drawBigString(430,30,stringLv,1);
	}else if (s == "new") {
		char buffer = lv->create();
		b->nextBlock(buffer, lv->getLv());
	}else if (s == "left") b->moveBlock('l');
	else if (s == "right") b->moveBlock('r');
	else if (s == "swap") {
		char buffer = lv->create();
		b->swapBlock(buffer);
	}
}
//------------------RESTART AND PRINT STUFF------------------//
void Game::restart() {
	if (b != NULL)delete b;
	b = new Board(xWin,display);
	while(lv->getLv() > 0) {
		lv->levelDown();
	}
	score = 0;
	this->startGame(display);
	this->runGame("new");
}

void Game::header() {
	cout << "Level:" << setw(10);
	cout << lv->getLv() << endl;

	cout << "Score:" << setw(10);
	cout << this->score << endl;

	cout << "Hi Score:" << setw(7);
	cout << this->hiScore << endl;
}

void Game::body() {
	cout << *b;
}
