#ifndef ZBLOCK_H_
#define ZBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 3; //block Z size is 3

class ZBlock: public Block {

public:
	ZBlock(); 			//constructor
	~ZBlock();			//destructor
	//ZBlock * create();	//overriding create()
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};




#endif /* ZBLOCK_H_ */
