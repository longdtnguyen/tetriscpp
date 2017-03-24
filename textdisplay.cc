#include "textdisplay.h"
#include <iostream>
using namespace std;

//constructor
TextDisplay::TextDisplay() {
	//char temp = 'A';
	int count = 0;
	theDisplay = new char*[MAX_ROW];
	for(int i=0;i<MAX_ROW;++i) {
		theDisplay[i] = new char[MAX_COL];
		for(int j=0;j<MAX_COL;++j) {
			theDisplay[i][j] = ' ';
			count++;
		}
	}
}

//destructor
TextDisplay::~TextDisplay() {
	for(int i=0;i<MAX_ROW;++i) {
		delete [] theDisplay[i];
	}
	delete theDisplay;
}

//notify display
void TextDisplay::notify(int r,int c,char type) {
	theDisplay[r][c] = type;
}

//overloading <<
ostream &operator<<(ostream &out,const TextDisplay &td) {
	out << string(10, '-') << endl;
	for(int i=0;i<MAX_ROW;++i) {
		for(int j=0;j<MAX_COL;++j) {
			out << td.theDisplay[i][j];
		}
		out << endl;
	}
	out << string(10, '-') << endl;
	return out;
}
