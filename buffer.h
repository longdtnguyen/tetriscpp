#ifndef BUFFER_H_
#define BUFFER_H_
 
#include <termios.h>
#define TSCANOW 0
#define STDIN_FILENO 0
class BufferToggle {
private:
	struct termios t;
public:
	void off(void); //disable buffer input
    void on(void) ; //enable buffer input
};

#endif /* BUFFER_H_ */
