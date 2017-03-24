#ifndef IBLOCK_H_
#define IBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 4; //block I size is 4

class IBlock: public Block {

public:
	IBlock(); 			//constructor
	~IBlock();			//destructor
	//IBlock * create();	//overriding create()
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow * xWin); //override draw
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};

#endif /* IBLOCK_H_ */
