#ifndef JBLOCK_H_
#define JBLOCK_H_

#include "block.h"

//#define BLOCK_SIZE 3; //block J size is 3

class JBlock: public Block {

public:
	JBlock(); 			//constructor
	~JBlock();			//destructor
	//JBlock * create();	//overriding create()
	void rClock();		//overriding rClock()
	void rcClock();		//overriding rcClock()
	void draw(Xwindow *xWin);
	void draw(Xwindow * xWin,int seed,int seed2); //overload+ override draw
};





#endif /* JBLOCK_H_ */
