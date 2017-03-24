#ifndef LEVEL_H_
#define LEVEL_H_
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
//#define MAXLV 4
class Level {
	int lv;
	std::ifstream inF;
	int seed;
	std::string daf;
public:
	Level(); //constructor
	~Level();
	Level(int n,int s,std::string f); //initate constructor
	int getLv() {return this->lv;};
	void levelUp(); //go up 1 level
	void levelDown(); //go down 1 level
	char create(); //create block according to level
};




#endif /* LEVEL_H_ */
