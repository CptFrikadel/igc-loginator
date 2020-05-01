CC = g++

CFLAGS = -g

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp
OBJ = Logbook.o IGCReader.o main.o

%.o: %.cpp $(DEPS)
	$(CC) -Wall -c -o $@ $< $(CFLAGS)

logbook: $(OBJ)
	$(CC) -Wall -o $@ $^ $(CFLAGS)

clean:
	rm *.o
