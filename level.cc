#include "level.h"
#include <cstdlib>
#include <ctime>
using namespace std;

//Constructors
Level::Level():lv(0),seed(-1),daf("sequence.txt"){}
Level::Level(int n,int s,string f):lv(n),seed(s),daf(f) {
	inF.open(f.c_str());
}

//destructor
Level::~Level() {}
//Level up
void Level::levelUp(){
	lv++;
}

//Level down
void Level::levelDown(){
	if (lv > 0) lv--;
}

//Return a char based on current difficulty
char Level::create(){
	//seed the stuff
	if (seed == -1) srand(time(NULL));
	else srand(seed);
	//--------------//
	if (lv == 0){
		string temp;
		if (inF >> temp) return temp[0];
		else {
			inF.clear();
			inF.close();
			inF.open(daf.c_str());
			inF >> temp;
			return temp[0];
		}
	}
	else if(lv == 1){
		int n = rand() % 12;
		if(n == 0) return 'S';
		else if (n == 1) return 'Z';
		else if (n < 4) return 'I';
		else if (n < 6) return 'O';
		else if (n < 8) return 'L';
		else if (n < 10) return 'J';
		else if (n < 12) return 'T';
	}
	else if(lv == 2){
		int n = rand() % 7;
		if(n == 0) return 'S';
		else if (n < 2) return 'Z';
		else if (n < 3) return 'I';
		else if (n < 4) return 'O';
		else if (n < 5) return 'L';
		else if (n < 6) return 'J';
		else if (n < 7) return 'T';
	}
	else if(lv >= 3){
		int n = rand() % 9;
		if (n < 2) return 'S';
		else if (n < 4) return 'Z';
		else if (n < 5) return 'I';
		else if (n < 6) return 'O';
		else if (n < 7) return 'L';
		else if (n < 8) return 'J';
		else if (n < 9) return 'T';
	}
	return 'I';
}



