#ifndef TEXTDISPLAY_H_
#define TEXTDISPLAY_H_
#include <iostream>
#define MAX_ROW 18
#define MAX_COL 10
class TextDisplay {
	char **theDisplay;
public:
	TextDisplay(); //constructor
	~TextDisplay(); //destructor
	void notify(int r,int c,char type);

	friend std::ostream &operator<<(std::ostream &out,const TextDisplay &td);
};



#endif /* TEXTDISPLAY_H_ */
