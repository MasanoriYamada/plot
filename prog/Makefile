CXX = g++

SRC_DIR = .
INC_DIR = ../include

INC_1 = $(INC_DIR)/gnuplot.h
INC_LST= $(INC_1)

SRC_LST=$(wildcard $(addsuffix /*.cpp,$(SRC_DIR)))


all: plot.out
debug:debug.out
plot.out:$(INC_LST) $(SRC_LST)
	$(CXX) -o $@ $(SRC_LST)
debug.out:$(INC_LST) $(SRC_LST)
	$(CXX) -g -o $@ $(SRC_LST)
clean:
	rm ./*.o ./*.out ./*tmpForDrowing.dat
