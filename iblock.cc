#include "iblock.h"
//#include "block.h"
using namespace std;

IBlock::IBlock():Block('I',0,0,4,0) {
	changeBlock(3,0,1);
	changeBlock(3,1,1);
	changeBlock(3,2,1);
	changeBlock(3,3,1);
}


void IBlock::rClock(){

	if (getState()==1){			//Check state
		changeState(-1);
	}
	else{
		changeState(1);
	}
	int tsize = getSize();
	bool temp[tsize][tsize];
	for(int i=0; i<tsize; i++){		//set Temp block to empty
		for(int j=0; j<tsize; j++){
			temp[i][j] = false;
		}
	}
	if(getState() == 0) {
		temp[3][0] = 1;
		temp[3][1] = 1;
		temp[3][2] = 1;
		temp[3][3] = 1;
	}else {
		temp[0][0] = 1;
		temp[1][0] = 1;
		temp[2][0] = 1;
		temp[3][0] = 1;
	}
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			changeBlock(i,j,temp[i][j]);
		}
	}
}

void IBlock::rcClock(){
	rClock();
}
//draw
void IBlock::draw(Xwindow * xWin) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+getY()),25*(i+getX()),25,25,1);
				xWin->fillRectangle(25*(j+getY())+1,25*(i+getX())+1,23,23,3);
			}
		}
	}
}

void IBlock::draw(Xwindow * xWin,int seed,int seed2) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+seed2),25*(i+seed),25,25,1);
				xWin->fillRectangle(25*(j+seed2)+1,25*(i+seed)+1,23,23,3);
			}
		}
	}
}
IBlock::~IBlock(){
}
//IBlock::~IBlock(){}
