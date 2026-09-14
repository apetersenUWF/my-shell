CXX = g++
CXXFLAGS = -std=c++11 -Wall -g

# Object file names
MAINDRIVER = main.o
TESTDRIVER = test.o
INCLUDE = param.o parse.o

# Executable file names
EXEC = run
TEST = test

TEXT_FILES =

# Main targets
run: $(INCLUDE) $(MAINDRIVER)
	$(CXX) $(CXXFLAGS) -o $@ $(INCLUDE) $(MAINDRIVER)

test: $(INCLUDE) $(TESTDRIVER)
	$(CXX) $(CXXFLAGS) -o $@ $(INCLUDE) $(TESTDRIVER)

clean:
	rm -f $(EXEC) $(TEST) $(TEXT_FILES) $(INCLUDE) $(MAINDRIVER) $(TESTDRIVER)

# Object targets
param.o:
	$(CXX) $(CXXFLAGS) -c param.cpp -o param.o

parse.o:
	$(CXX) $(CXXFLAGS) -c parse.cpp -o parse.o

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

test.o:
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o