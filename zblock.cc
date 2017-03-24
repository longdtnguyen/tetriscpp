#include "zblock.h"
#include "block.h"
using namespace std;

//
ZBlock::ZBlock():Block('Z',0,2,3,0) {
	this->changeBlock(1,0,1);
	this->changeBlock(1,1,1);
	this->changeBlock(2,1,1);
	this->changeBlock(2,2,1);
}

void ZBlock::rClock(){
	if(getState()==1) this->changeState(-1);
	else this->changeState(1);
	int tsize = getSize();
	bool temp[tsize][tsize];
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			temp[i][j] = false;
		}
	}
	if(getState()==0){
		temp[1][0] = true;
		temp[1][1] = true;
		temp[2][1] = true;
		temp[2][2] = true;
	}
	else if(getState()==1){

		temp[0][1] = true;
		temp[1][0] = true;
		temp[1][1] = true;
		temp[2][0] = true;
	}
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			changeBlock(i,j,temp[i][j]);
		}
	}
}

void ZBlock::rcClock(){
	rClock();
}
void ZBlock::draw(Xwindow * xWin) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+getY()),25*(i+getX()),25,25,1);
				xWin->fillRectangle(25*(j+getY())+1,25*(i+getX())+1,23,23,9);
			}
		}
	}
}

void ZBlock::draw(Xwindow * xWin,int seed,int seed2) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+seed2),25*(i+seed),25,25,1);
				xWin->fillRectangle(25*(j+seed2)+1,25*(i+seed)+1,23,23,9);
			}
		}
	}
}
ZBlock::~ZBlock() {}
