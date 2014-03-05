CXX       = g++
CXXFLAGS  = -g -O2 -I/usr/local/include/SDL2
LDFLAGS   = -lSDL2_test -Wl,-rpath,/usr/local/lib -L/usr/local/lib -lSDL2 -lpthread

all:
	$(CXX) ./src/main.cpp $(CXXFLAGS) $(LDFLAGS)
