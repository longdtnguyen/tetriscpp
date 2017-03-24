#ifndef BOARD_H_
#define BOARD_H_

#include "block.h"
#include "textdisplay.h"
#include "window.h"

#define COL 10
#define ROW 18
#define NUM_BLOCK 10;
class Block;
class Board {
	bool display;
	bool **theBoard; //the initial board
	TextDisplay *td; //textdisplay
	Xwindow * xWin;
	Block *barr[1024]; //array of pointer to the blocks
	int lv[1024];
	int numBlock; //number of block in array
	Block *nextB; //next block
	Block *swapB; //block to swap
	bool over;
	bool canSwap;
public:
	Xwindow * winOut() { return this->xWin; };
	void notify(int r,int c,bool n);
	void clearBoard(); //clears all contents of board, and block array
	Board(Xwindow *w, bool b); //constructor
	~Board(); //detructor
	int clearEmpty(); // returns level values of cleared blocks
	int currentX(); //returns x val of current block.
	bool isOver() { return this->over; }; //check isOver for game
	void dropBlock(); // drop the block
	void rotateBlock(char c);
	void moveBlock(char dir); //move the block left right
	int clearRow(); //clear the row, return the number of row cleared
	void firstBlock(char type);
	void nextBlock(char type, int val); //create the block with type
	bool checkColl(Block *p); //checking collision
	bool gameOver(); //check the end of the game
	//-----------SWAP-----//
	void swapBlock(char type); //swap
	 friend std::ostream& ::operator<<(std::ostream &out, const Board &b);
};




#endif /* BOARD_H_ */
