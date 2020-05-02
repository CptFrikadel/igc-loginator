CXX = g++

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp
OBJ = Logbook.o IGCReader.o main.o

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CFLAGS)

clean:
	rm *.o
