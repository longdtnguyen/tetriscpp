#ifndef SBLOCK_H_
#define SBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 3; //block S size is 3

class SBlock: public Block {

public:
	SBlock(); 			//constructor
	~SBlock();			//destructor
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};





#endif /* SBLOCK_H_ */
