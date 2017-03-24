#include "lblock.h"
#include "block.h"
using namespace std;

LBlock::LBlock():Block('L',0,2,3,0){
	//initiate the stage
	this->changeBlock(1,2,1);
	this->changeBlock(2,0,1);
	this->changeBlock(2,1,1);
	this->changeBlock(2,2,1);
}

void LBlock::rClock(){
	if(getState()==3) changeState(-3);
	else changeState(1);
	const int tsize = getSize();
	bool temp[tsize][tsize];
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			temp[i][j] = false;
		}
	}
	if(getState()==0){
		temp[1][2] = true;
		temp[2][0] = true;
		temp[2][1] = true;
		temp[2][2] = true;
	}
	else if(getState()==1){

		temp[0][0] = true;
		temp[1][0] = true;
		temp[2][0] = true;
		temp[2][1] = true;
	}
	else if(getState()==2){
		temp[1][0] = true;
		temp[1][1] = true;
		temp[1][2] = true;
		temp[2][0] = true;
	}
	else{
		temp[0][1] = true;
		temp[1][1] = true;
		temp[2][1] = true;
		temp[0][0] = true;
	}
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			changeBlock(i,j,temp[i][j]);
		}
	}
}

void LBlock::rcClock(){
	if(getState()==0) changeState(3);
	else changeState(-1);
	const int tsize = getSize();
	bool temp[tsize][tsize];
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			temp[i][j] = false;
		}
	}
	if(getState()==0){
		temp[1][2] = true;
		temp[2][0] = true;
		temp[2][1] = true;
		temp[2][2] = true;
	}
	else if(getState()==1){

		temp[0][0] = true;
		temp[1][0] = true;
		temp[2][0] = true;
		temp[2][1] = true;
	}
	else if(getState()==2){
		temp[1][0] = true;
		temp[1][1] = true;
		temp[1][2] = true;
		temp[2][0] = true;
	}
	else{
		temp[0][1] = true;
		temp[1][1] = true;
		temp[2][1] = true;
		temp[0][0] = true;
	}
	for(int i=0; i<tsize; i++){
		for(int j=0; j<tsize; j++){
			changeBlock(i,j,temp[i][j]);
		}
	}
}
void LBlock::draw(Xwindow * xWin) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+getY()),25*(i+getX()),25,25,1);
				xWin->fillRectangle(25*(j+getY())+1,25*(i+getX())+1,23,23,2);
			}
		}
	}
}

void LBlock::draw(Xwindow * xWin,int seed,int seed2) {
	for(int i=0;i<getSize();++i) {
		for(int j=0;j<getSize();++j) {
			if(getCell(i,j) == 1) { 
				xWin->fillRectangle(25*(j+seed2),25*(i+seed),25,25,1);
				xWin->fillRectangle(25*(j+seed2)+1,25*(i+seed)+1,23,23,2);
			}
		}
	}
}
LBlock::~LBlock(){}
