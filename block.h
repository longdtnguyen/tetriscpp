#ifndef BLOCK_H_
#define BLOCK_H_
#include <cstdlib>
#include "textdisplay.h"
#include "window.h"
#include "board.h"
#include <iostream>
class Board;
class Block {
	char type;
	int x,y; //coordinate
	int oriX,oriY;
	int size;
	int state;
	bool hasRow(int n);
	void swapRow(bool *r1, bool *r2);
	//-------------------//
	int xw,yw,width,height;
	bool **theBlock;
public:
	//accessor and changees
	void coordReset() {x = oriX; y =oriY;};
	int getState() {return this->state;};
	void changeState(int change) {this->state += change;};
	char getType() { return this->type; };
	int getX() {return this->x;};
	int getY() {return this->y;};
	void changeX(int inc) {this->x++;} ;
	void changeY(int inc) {this->y++;} ;
	int getSize() {return this->size;} ;
	void changeBlock(int r,int c,bool val) {this->theBlock[r][c] = val;} ;
	bool getCell(int r,int c) {
		if(r<size && r>=0 && c<size && c>=0) return theBlock[r][c];
		return 0;
	};
	bool hasCell(int r, int c);

	//--------------------//
	Block(); 					//constructor
	Block(char type,int x,int y,int size,int state);
	void notifyDisplay(TextDisplay &td,bool n);
	void notifyBoard(Board &b,bool n);
	virtual ~Block();				//destructor
	virtual void rClock()=0;	//rotate clockwise
	virtual void rcClock()=0;	//rotate counterclockwise
	void move(char c);
	bool isEmpty(); //Check block status
	void  clearRow(int n); //Clears cells in the given row.

	//-------WINDOW-----------//
	virtual void draw(Xwindow *wd) =0;
	virtual void draw(Xwindow *wd,int seed,int seed2) =0;
	void undraw(Xwindow *wd);
	void undraw(Xwindow *wd,int seed,int seed2);
};
#endif /* BLOCK_H_ */
