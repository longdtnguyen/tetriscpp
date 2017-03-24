#include "block.h"
#include <algorithm>
using namespace std;

Block::Block()/*type(' '),x(0),y(0),size(0),state(0),theBlock(NULL)*/ {};

//the subclass call this
Block::Block(char t,int ty,int tx,int tsize, int tstate):
		type(t),x(tx),y(ty),size(tsize),state(tstate) {
	theBlock = new bool*[this->size];
	for(int i=0;i<size;++i) {
		theBlock[i] = new bool[this->size];
		for(int j=0;j<size;++j) {
			theBlock[i][j] = 0;
		}
	}
	oriX = x;
	oriY = y;
}
//--------------------------NOTIFY-----------------------//

//notifydisplay (Board call this)
void Block::notifyDisplay(TextDisplay &td,bool n) {
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(n ==0 && theBlock[i][j] == 1) td.notify(i+x,j+y,' ');
			else {
				if(theBlock[i][j] == 1) td.notify(i+x,j+y,type);
			}
		}
	}
}

//notifyboard (Board also call this)
void Block::notifyBoard(Board &b,bool n) {
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(n == 0 && theBlock[i][j] == 1)  b.notify(i+x,j+y,0); 
			else{
				if(theBlock[i][j] == 1) b.notify(i+x,j+y,1);
			}
		}
	}
}

//check if Cell is in the given block
bool Block::hasCell(int r, int c){
	for(int i=0; i<size; i++){
		for(int j=0; j<size; j++){
			if (theBlock[i][j] && i+x == r && j+y == c) return true;
		}
	}
	return false;
}

//-----------------------MOVE AND STUFF------------------//
void Block::move(char car){
	if (car == 'L'){
		y -= 1;
	}
	else if(car == 'R'){
		y += 1;
	}
	else if
	(car == 'D'){
		x += 1;
	}
	else if
	(car == 'U'){
		x -= 1;
	}
}

//Iterate through block, check if all empty.
bool Block::isEmpty(){
	for(int i=0; i<size;i++){
		for(int j=0; j<size;j++){
			if (theBlock[i][j]){
				return false;
			}
		}
	}
	return true;
}

//Check if block has a TRUE cell in row n
bool Block::hasRow(int n){
	if(x <= n){
		if((n-x) < size){
			for (int i=0; i<size; i++){
				if(theBlock[n-x][i]) return true;
			}
		}
	}
	return false;
}

//Swaps two rows within a block.
void Block::swapRow(bool *r1, bool *r2){
	for(int i=0; i<size; i++){
		bool temp = r1[i];
		r1[i] = r2[i];
		r2[i] = temp;
	}
}

//Clears a row in a block, then pushes all rows above it down.
void Block::clearRow(int n){
	if(hasRow(n)){
		int row = n-x;
		for(int i=0; i<size; i++){
			theBlock[row][i] = false;
		}
		for(int i=row; i>0; i--){
			swapRow(theBlock[i], theBlock[i-1]);
		}
	}
}
Block::~Block() {
	for(int i=0;i<size;++i) {
		delete []  theBlock[i];
	}
	delete [] theBlock;
};

//--------------------WINDOW AND STUFF--------------//


void Block::undraw(Xwindow *xWin) {
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(theBlock[i][j] == 1) xWin->fillRectangle(25*(j+y),25*(i+x),25,25,0);
		}
	}
}

void Block::undraw(Xwindow *xWin,int seed,int seed2) {
	for(int i=0;i<size;++i) {
		for(int j=0;j<size;++j) {
			if(theBlock[i][j] == 1) xWin->fillRectangle(25*(j+seed2),25*(i+seed),25,25,0);
		}
	}
}
