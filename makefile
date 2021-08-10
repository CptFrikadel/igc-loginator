

DEPS = Logbook.hpp IGCReader.hpp FlightData.hpp CursesTable.hpp DetailsWindow.hpp
OBJ = Logbook.o IGCReader.o main.o CursesTable.o DetailsWindow.o

LIBS = -lncurses

all: logbook

debug: CXXFLAGS += -g
debug: logbook

%.o: %.cpp $(DEPS)
	$(CXX) -Wall -c -o $@ $< $(CXXFLAGS)

logbook: $(OBJ)
	$(CXX) -Wall -o $@ $^ $(CXXFLAGS) $(LIBS)

.PHONY : clean
clean :
	-rm logbook $(OBJ)
