#ifndef TBLOCK_H_
#define TBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 3; //block T size is 3

class TBlock: public Block {

public:
	TBlock(); 			//constructor
	~TBlock();			//destructor
	//TBlock * create();	//overriding create()
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};





#endif /* TBLOCK_H_ */
