#include "oblock.h"
#include "block.h"
using namespace std;

OBlock::OBlock():Block('O',0,3,2,0) {
	//initiate the stage
	for(int i=0; i<getSize(); i++){
		for(int j=0; j<getSize(); j++){
			this->changeBlock(i,j,1);
		}
	}
}

void OBlock::rClock(){}

void OBlock::rcClock(){}
void OBlock::draw(Xwindow * xWin) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+getY()),25*(i+getX()),25,25,1);
				xWin->fillRectangle(25*(j+getY())+1,25*(i+getX())+1,23,23,8);
			}
		}
	}
}

void OBlock::draw(Xwindow * xWin,int seed,int seed2) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+seed2),25*(i+seed),25,25,1);
				xWin->fillRectangle(25*(j+seed2)+1,25*(i+seed)+1,23,23,8);
			}
		}
	}
}
OBlock::~OBlock() {}

