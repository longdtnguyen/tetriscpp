CXX = g++
CXXFLAGS = -Wall -MMD
DISPLAY = -L/usr/X11R6/lib -lX11 -g
EXEC = quadris
OBJECTS = main.o level.o game.o kbhit.o window.o buffer.o block.o iblock.o oblock.o tblock.o lblock.o jblock.o zblock.o sblock.o board.o textdisplay.o
DEPENDS = ${OBJECTS:.o=.d}
${EXEC}: ${OBJECTS}
		  ${CXX} ${CXXFLAGS} ${OBJECTS} ${DISPLAY} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean
clean:
		rm ${OBJECTS} ${EXEC} ${DEPENDS}
