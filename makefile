CXX = g++

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp CursesTable.hpp
OBJ = Logbook.o IGCReader.o main.o CursesTable.o

LIBS = -lcurses

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CFLAGS) $(LIBS)

clean:
	rm *.o
