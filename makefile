

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp CursesTable.hpp FlightList.hpp
OBJ = Logbook.o IGCReader.o main.o CursesTable.o FlightList.o

LIBS = -lncurses

all: logbook

CXXFLAGS = -std=gnu++20

debug: CXXFLAGS += -g 
debug: logbook

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CXXFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY : clean
clean :
	-rm logbook $(OBJ)
