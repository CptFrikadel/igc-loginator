CXX = g++

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp
OBJ = Logbook.o IGCReader.o main.o

LIBS = -lcurses

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm *.o
