#include "buffer.h"

void BufferToggle::off() {
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag &= ~ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
}

void BufferToggle::on()  {
    tcgetattr(STDIN_FILENO, &t); //get the current terminal I/O structure
    t.c_lflag |= ICANON; //Manipulate the flag bits to do what you want it to do
    tcsetattr(STDIN_FILENO, TSCANOW, &t); //Apply the new settings
}

