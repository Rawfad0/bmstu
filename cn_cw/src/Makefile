CXX = clang++
CXXFLAGS = -Wall -Wextra -std=c++17 -O2

SRC = main.cpp http_server.cpp logger.cpp
OBJ = $(SRC:.cpp=.o)
BIN = a.out

all: $(BIN)

%.o: %.cpp consts.h
	$(CXX) $(CXXFLAGS) -c $<

$(BIN): $(OBJ) consts.h
	$(CXX) $(CXXFLAGS) -o $(BIN) $(OBJ)


load_test1: load_test1.cpp
	$(CXX) $(CXXFLAGS) -o load_test1 load_test1.cpp

load_test2: load_test2.cpp
	$(CXX) $(CXXFLAGS) -o load_test2 load_test2.cpp

clean:
	rm -f $(OBJ) $(BIN) load_test1 load_test2
