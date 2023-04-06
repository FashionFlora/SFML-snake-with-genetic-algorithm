CXX = g++
# CXXFLAGS = -std=c++14 -Wall -MMD
CXXFLAGS = -Wall -MMD
EXEC = snake
OBJECTS = main.o game.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
