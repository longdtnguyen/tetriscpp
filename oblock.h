#ifndef OBLOCK_H_
#define OBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 2; //block O size is 2

class OBlock: public Block {

public:
	OBlock(); 			//constructor
	~OBlock();			//destructor
	//OBlock * create();	//overriding create()
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};



#endif /* OBLOCK_H_ */
