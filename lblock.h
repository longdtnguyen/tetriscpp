#ifndef LBLOCK_H_
#define LBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 3; //block L size is 3

class LBlock: public Block {

public:
	LBlock(); 			//constructor
	~LBlock();			//destructor
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};

#endif /* LBLOCK_H_ */
