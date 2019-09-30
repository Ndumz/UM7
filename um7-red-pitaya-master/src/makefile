CXX = gcc
FLAGS = -std=c99 -L lib -lm -lpthread -lserialport

DEPS = imu.h colour.h binary.h
OBJ = main.o imu.o colour.o binary.o

%.0: %.c $(DEPS)
	$(CXX) -c -o $@ $< $(FLAGS)
	
um7red: $(OBJ)
	$(CXX) -o $@ $^ $(FLAGS)
	
run:

clean:
	@rm *.o
	
