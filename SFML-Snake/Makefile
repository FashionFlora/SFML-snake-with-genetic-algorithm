CXX = g++
# CXXFLAGS = -std=c++14 -Wall -MMD
CXXFLAGS = -Wall -MMD
EXEC = snakeai
OBJECTS = main.o Snake/game.o SimpleNeuralNetwork/NeuralNetwork.o SimpleNeuralNetwork/GeneticAlgorithm.o Population.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${EXEC} ${OBJECTS} ${DEPENDS}
