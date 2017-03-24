#include <string>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "board.h"
#include "block.h"
#include "buffer.h"
#include "level.h"
#include "textdisplay.h"
#include "window.h"
#include "game.h"

#include "oblock.h"
#include "zblock.h"
#include "lblock.h"
#include "tblock.h"
#include "jblock.h"
#include "iblock.h"
#include "sblock.h"
#include <unistd.h>
#include "kbhit.h"

using namespace std;
int main(int argc,char *argv[]) {
	//arrow key class-- dont you dare changing this//
	BufferToggle bt;	
	bool key=0;			//control flow for key or command
	string s;			//buffer for command
	char c;				//buffer for arrow key
	bool done=0;		//for the arrow key
	int startLv=0;		//start at Lv
	int seed=-1;	//seed for random generation
	bool display=1; // decide whether open the display or not
	bool realT =0;
	string inF = "sequence.txt"; //infile
	float speed = 2.75;
	Xwindow * xw;
	//--------------------------------------------//
	
	//command option
	if (argc -1 != 0) {
		for(int i=1;i < argc;++i) {
			string getCom = argv[i];
			if(getCom == "-text") {
				display = 0;
			}else if(getCom == "-seed") {
				++i;
				getCom = argv[i];
				istringstream (getCom) >> seed;
			}else if(getCom == "-scriptfile") {
				++i;
				inF = argv[i];
			}else if(getCom == "-startlevel") {
				++i;
				getCom = argv[i];
				istringstream (getCom) >> startLv;
			}else if(getCom == "-realtime") {
				realT = 1;
			}
		}
	}
	//--------------------------------------------//
	if(display) {
		xw = new Xwindow();
		usleep(100000);
		xw->drawBigString(80,150,"Tetris",9);
		xw->drawBigString(50,200,"Developed by:",9);
		xw->drawBigString(50,250,"L.A.N.T Studios",10);
		usleep(3000000);
	}
	Game *g = new Game(seed,startLv,xw,inF,display);
	g->startGame(display);
	cout << "choose input method: \"command\" or \"key\"" << endl;
	cin >> s;
	//input command type control flow
	if (s == "command") {
		key = 0;
		bt.on();
	}else {
		key = 1;
		bt.off();
	}
	//-----------------------------//
	//command 
	if(key ==0) {
		system("clear");
		cout << "Enter your command here: " << endl;
		g->runGame("new");
		g->header();
		g->body();
		while(cin >>s) {
			//buffer the input
			string buffer = "";
			int pos =0; //to get the number in the command
			long int num=1;	//actual nummber
			while(s[pos] >= 48 && s[pos] <= 57) {
				buffer += s[pos];
				++pos;
			}
			//----------------//
			system("clear");
			if (buffer != "") {
				istringstream ss(buffer);
				ss >> num;
			}
			if(s[pos] != 'c' && num>15) num =15;
			if(num <= 0) {
				g->header();
				g->body();
			}
			//control stuff (ugly stuff)
			if(s[pos] == 'l') {	//case left, levelUp,levelDown
				pos += 2;
				if(s[pos] == 'f') {   //case left
					for(int i=1;i<= num;++i) {
						system("clear");
						g->runGame("left");
						g->header();
						g->body();
						usleep(150000);
					}
				}else { 					//case level
					pos += 3;
					if(s[pos] == 'u') {   //up
						for(int i=1;i<=num;++i) g->runGame("levelup");
						g->header();
						g->body();
					}else if(s[pos] == 'd') {  //down
						for(int i=1;i<=num;++i) g->runGame("leveldown");
						g->header();
						g->body();
					}
				}
			}else if(s[pos] == 'r') {   //case right,restart
				pos++;
				if(s[pos] == 'i') {  //right
					for(int i=1;i<=num;++i) {
						system("clear");
						g->runGame("right");
						g->header();
						g->body();
						usleep(150000);
					
					}
				}else if(s[pos] == 'e') { //restart
					g->restart();
					g->header();
					g->body();
				}
			}else if(s[pos] == 'd') {   //case drop and down
				pos++;
				if(s[pos] == 'r') {  //drop
					system("clear");
					g->runGame("drop");
					g->header();
					g->body();
				}else if(s[pos] == 'o') { //down
					for(int i=1;i<=num;++i) {
						system("clear");
						g->runGame("down");
						g->header();
						g->body();
						usleep(150000);
					}
				}
			}else if(s[pos] == 'c') { //rotate (both way)
				pos++;
				if(s[pos] == 'l') { //clockwise
					for(int i=1;i<=num;++i) {
						system("clear");
						g->runGame("rotate");
						g->header();
						g->body();
						usleep(150000);
					}
				}else if(s[pos] == 'o') { //counterclockwise
					for(int i=1;i<=num;++i) {
						system("clear");
						g->runGame("crotate");
						g->header();
						g->body();
						usleep(150000);
					}
				}
			}else if(s[pos] == 'q') break;  //quit case
			else if(s[pos] == 's') {  //swap case
				system("clear");
				g->runGame("swap");
				g->header();
				g->body();
			}
		}
	
	//run this loop if take the command by arrow key
	}else {
		cout << "You set the input method to arrow keys" << endl;
		//system("clear");
		g->runGame("new");
		g->header();
		g->body();
		while(!done) {
			if(realT) {
				time_t rawTime;
				time(&rawTime);
					if(g->levelOut() < 2) speed =2;
					if(g->levelOut() > 2) speed =1;
				while(!kbhit()) {
					time_t timeNow;
					time(&timeNow);
					float temp = difftime(timeNow,rawTime);
					if(temp >= speed) {
						system("clear");
						g->runGame("down");
						g->header();
						g->body();
						time(&rawTime);
					}
				}
			}
			cin>>c;
			switch(c) {
				system("clear");
				case 'A': //up arrow key
					g->runGame("rotate");
					g->header();
					g->body();
					break;
				case 'B': //down arrow key
					g->runGame("down");
					g->header();
					g->body();
					break;
				case 'C': //right key
					g->runGame("right");
					g->header();
					g->body();
					break;
				case 'D'://left key
					g->runGame("left");
					g->header();
					g->body();
					break;
				case 'n':
					g->restart();
					g->header();
					g->body();
					break;
				case 'q':
					done =1 ;
					break;
				case 'd':
					g->runGame("drop");
					g->header();
					g->body();
					break;
				case 's':
					g->runGame("swap");
					g->header();
					g->body();
				default:
//					cout << "wrong command, try again" << endl;
					break;
			}
		//	flag = 0;
		}		
	
	}
	delete xw;
	delete g;
}
