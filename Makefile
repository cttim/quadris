CXX = g++
CXXFLAGS = -Wall -MMD
OBJECTS = grid.o cell.o block.o driver.o window.o scoreboard.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = final

${EXEC} : ${OBJECTS}
	${CXX} ${OBJECTS} -L/usr/X11R6/lib -lX11 -o ${EXEC}

-include ${DEPENDS}

clean :
	rm -rf ${DEPENDS} ${OBJECTS} ${EXEC}
.PHONY : clean
