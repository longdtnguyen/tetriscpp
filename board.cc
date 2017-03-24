#include "board.h"
#include "lblock.h"
#include "oblock.h"
#include "iblock.h"
#include "tblock.h"
#include "sblock.h"
#include "zblock.h"
#include "jblock.h"
#include <algorithm>
#include <cstdlib>
#include <cmath>
using namespace std;
//-------------------------------------------------------------------//
//-------------------------CREATE AND DESTROY------------------------//
//-------------------------------------------------------------------//

//=========CREATE=======//
//constructor
Board::Board(Xwindow *xw, bool b):numBlock(-1), over(0){
	nextB=NULL;
	swapB=NULL;
	canSwap =1;
	//get the new display
	display = b;
	td= new TextDisplay();
	xWin = xw;
	//inititalize the board
	theBoard = new bool*[ROW];
	for(int i=0;i<ROW;++i) {
		theBoard[i] = new bool[COL];
		//set all the board element to 0
		for(int j=0;j<COL;++j) {
			theBoard[i][j] = 0;
		}
	}
}


//=========DESTROY STUFFS========//

//clear the board
void Board::clearBoard() {
	//delete the board
	if(theBoard != NULL) {
		for(int i=0;i<ROW;++i) {
			delete [] theBoard[i];
		}
		delete theBoard;
	}
	//delete the array of the block
	for(int i=0;i<=numBlock;++i) {
		if(display)barr[i]->undraw(xWin);
		delete barr[i];
	}
	delete [] barr;
	delete [] lv;
	delete nextB;
	delete swapB;
}

//destructor
Board::~Board() {
	clearBoard();
	//delete the textdisplay
	if(td != NULL) delete td;
	if(nextB != NULL) delete nextB;
	if(swapB != NULL) delete swapB;
}

int Board::currentX(){
	return barr[numBlock]->getX();
}

//check if end of the game
bool Board::gameOver() {
	for(int i=0; i<nextB->getSize(); i++){
		for(int j=0; j<nextB->getSize(); j++){
			if(nextB->getCell(i,j) && theBoard[nextB->getX()+i][nextB->getY()+j])return true;
		}
	}
	return false;
}

//clear the winning row
int Board::clearRow() {
	int numRows = 0;			//counter for how many rows cleared
	for(int i = 0; i<ROW; i++){        //Check all the cells in every row    
		for(int j = 0; j<COL; j++){
			if(!theBoard[i][j]) break;    //don't continue checking a row when there is empty slot
			if(j == COL - 1){					//If Row is completely full
				cout << barr[numBlock]->getType() << endl;
				for(int k = 0; k<=numBlock; k++){  //Clear all blocks containing that row
					barr[k]->notifyBoard(*this,0);
					barr[k]->notifyDisplay(*td,0);
					if(display) barr[k]->undraw(xWin);
				   barr[k]->clearRow(i);
					barr[k]->notifyBoard(*this,1);
					barr[k]->notifyDisplay(*td,1);
					if(display) barr[k]->draw(xWin);
				}
				numRows++;	// Add to row counter
				for(int k = 0; k<numBlock; k++){ //Move all blocks above row down
					if(barr[k]->getX()<i){
						barr[k]->notifyBoard(*this,0);
						barr[k]->notifyDisplay(*td,0);
						if(display) barr[k]->undraw(xWin);
						barr[k]->move('D');
						if(checkColl(barr[k])) barr[k]->move('U');
						barr[k]->notifyBoard(*this,1);
						barr[k]->notifyDisplay(*td,1);
						if(display) barr[k]->draw(xWin);
					}
				}
			}
		}
	}
	return numRows;
}

//-----------CREATE STUFF----------------//

//geting the nextblock
void Board::firstBlock(char t) {
	//draw the board
	if(display) {
		xWin->fillRectangle(0,0,500,500,0);
		xWin->fillRectangle(250,0,2,450,1);
		xWin->fillRectangle(0,450,252,2,1);
		xWin->fillRectangle(0,75,250,1,8);
		xWin->fillRectangle(250,100,248,2,1);
	}
	//----------------------------//
	if(t == 'L') nextB = new LBlock();
	else if(t =='I') nextB = new IBlock();
	else if(t == 'O') nextB = new OBlock();
	else if(t == 'Z') nextB = new ZBlock();
	else if(t == 'J') nextB = new JBlock();
	else if(t == 'S') nextB = new SBlock();
	else if(t == 'T') nextB = new TBlock();
	if(display) {
		xWin->fillRectangle(252,300,248,2,1);
		xWin->drawBigString(260,340,"Next Block: ",1);
		xWin->drawBigString(260,135,"Swap: ",1);
		nextB->draw(xWin,14,14);
	}
}

//create the next block
void Board::nextBlock(char t, int val) {
	if(!gameOver()){
		numBlock++;
		barr[numBlock] = nextB;
		lv[numBlock] = val;
		if(display) nextB->undraw(xWin,14,14);
		if(t =='L') nextB = new LBlock();
		else if(t == 'I') nextB = new IBlock();
		else if(t == 'O') nextB = new OBlock();
		else if(t == 'Z') nextB = new ZBlock();
		else if(t == 'J') nextB = new JBlock();
		else if(t == 'S') nextB = new SBlock();
		else if(t == 'T') nextB = new TBlock();
		barr[numBlock]->notifyDisplay(*td,1);
		barr[numBlock]->notifyBoard(*this,1);
		if(display) {
			barr[numBlock]->draw(xWin);
			nextB->draw(xWin,14,14);
		}
	}
	else {
	over = true;
	}
}

int Board::clearEmpty(){
	int counter = 0;
	for(int i = 0; i<=numBlock; i++){
		if(barr[i]->isEmpty()){
			counter += pow(lv[i]+1,2);
			lv[i] = -1;
		}
	}
	return counter;
}
//swap the block
void Board::swapBlock(char t) {
	if(canSwap) {
		barr[numBlock]->notifyBoard(*this,0);
		barr[numBlock]->notifyDisplay(*td,0);	
		if(display) barr[numBlock]->undraw(xWin);
		barr[numBlock]->coordReset();
		canSwap = 0 ;
		if(swapB != NULL) {
			if(display) swapB->undraw(xWin,7,14);
			swapB->coordReset();
			swap(barr[numBlock],swapB);
			barr[numBlock]->notifyDisplay(*td,1);	
			barr[numBlock]->notifyBoard(*this,1);
			if(display) {
				barr[numBlock]->draw(xWin);
				swapB->draw(xWin,7,14);
			}
		}else{
			swapB = barr[numBlock];
			barr[numBlock] = nextB;
			if(display) nextB->undraw(xWin,14,14);
			if(t =='L') nextB = new LBlock();
			else if(t == 'I') nextB = new IBlock();
			else if(t == 'O') nextB = new OBlock();
			else if(t == 'Z') nextB = new ZBlock();
			else if(t == 'J') nextB = new JBlock();
			else if(t == 'S') nextB = new SBlock();
			else if(t == 'T') nextB = new TBlock();	
			barr[numBlock]->notifyDisplay(*td,1);	
			barr[numBlock]->notifyBoard(*this,1);
			if(display) {
				barr[numBlock]->draw(xWin);
				nextB->draw(xWin,14,14);
				swapB->draw(xWin,7,14);
			}
		}
	}
}
//ostream overloading
ostream& operator<<(ostream &out, const Board &b) {
	out << *(b.td);
	cout << "Swap: " << endl;
	if(b.swapB != NULL) {
		bool count1 =0;
		for(int i=0;i<b.swapB->getSize();++i) {
			for(int j=0;j<b.swapB->getSize();++j) {
				if(b.swapB->getCell(i,j) == 1) {
					cout << b.swapB->getType();
					count1 =1;
				}else if(count1) cout << ' ';
			}
			if (count1) cout << endl;
		}
	}
	cout << "Next: " << endl;
	bool count =0;
	for(int i=0;i<b.nextB->getSize();++i) {
		for(int j=0;j<b.nextB->getSize();++j) {
			if(b.nextB->getCell(i,j) == 1) {
				cout << b.nextB->getType();
				count =1;
			}else if(count) cout << ' ';
		}
		if (count) cout << endl;
	}
	return out;
}

//-----------------------------------------------------------//

//----------------------------------------------------------//
//----------------------MOVE AND STUFF----------------------//
//----------------------------------------------------------//


//CHECK FOR COLLISIONS BEFORE A MOVE.
bool Board::checkColl(Block *p){
	for(int i = 0; i<p->getSize(); i++){
		for(int j = 0; j<p->getSize(); j++){
			int r = i+p->getX();
			int c = j+p->getY();
			if(p->hasCell(r,c)){
				if (r>=0 && r<ROW && c>=0 && c<COL){
					if(theBoard[r][c])return true;
				}
				else return true;
			}
      }
	}
	return false;
}


//notify theboard (the block call this)
void Board::notify(int x,int y,bool n) {
	theBoard[x][y] = n;
}
void Board::moveBlock(char dir) {
	//delete the last location
	barr[numBlock]->notifyBoard(*this,0);
	barr[numBlock]->notifyDisplay(*td,0);
	if(display) {
		barr[numBlock]->undraw(xWin);
		xWin->fillRectangle(0,75,252,1,8);
	}
	//move and notify new location
	if(dir == 'd' || dir == 'D'){
		barr[numBlock]->move('D');
		if(checkColl(barr[numBlock]))barr[numBlock]->move('U');
	//	else cout <<" collision" << endl;
	}
	if(dir == 'l' || dir == 'L'){
		barr[numBlock]->move('L');
		if(checkColl(barr[numBlock]))barr[numBlock]->move('R');
	//	else cout << "collision" << endl;
	}
	if(dir == 'r' || dir == 'R'){
		barr[numBlock]->move('R');
		if(checkColl(barr[numBlock]))barr[numBlock]->move('L');
	//	else cout << "collision" << endl;
	}	
	barr[numBlock]->notifyBoard(*this,1);
	barr[numBlock]->notifyDisplay(*td,1);
	if(display) barr[numBlock]->draw(xWin);
}

void Board::dropBlock(){
	int temp = -1;
	int perm = barr[numBlock]->getX();
	while (temp != perm){
		perm = barr[numBlock]->getX();
		moveBlock('D');
		temp = barr[numBlock]->getX();
	}
	canSwap =1;
}

void Board::rotateBlock(char c) {
	//delete the last position
	barr[numBlock]->notifyBoard(*this,0);
	barr[numBlock]->notifyDisplay(*td,0);
	if(display) {
		barr[numBlock]->undraw(xWin);
		xWin->fillRectangle(0,75,252,1,8);
	}
	//try to rotate the block
	if (c == 'c'){
		barr[numBlock]->rClock();
		if(checkColl(barr[numBlock]))barr[numBlock]->rcClock();
	}
	else{
		barr[numBlock]->rcClock();
		if(checkColl(barr[numBlock]))barr[numBlock]->rClock();
	}
	//notify the new position of the block
	barr[numBlock]->notifyBoard(*this,1);
	barr[numBlock]->notifyDisplay(*td,1);
	if(display) barr[numBlock]->draw(xWin);
}
