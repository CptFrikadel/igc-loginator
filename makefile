CC = g++

CFLAGS = -g

DEPS = flightdata.hpp
OBJ = flightdata.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

logbook: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)  

clean:
	rm *.o
