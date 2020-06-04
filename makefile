CXX = g++

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp CursesTable.hpp
OBJ = Logbook.o IGCReader.o main.o CursesTable.o

LIBS = -lncurses

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CXXFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY : clean
clean :
	-rm logbook $(OBJ)
