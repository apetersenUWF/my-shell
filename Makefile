CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Object file names
SHELLDRIVER = myshell.o
TESTDRIVER = test.o
INCLUDE = param.o parse.o

# Executable file names
EXEC = myshell
TEST = test

TEXT_FILES =

# Main targets
run: $(INCLUDE) $(SHELLDRIVER)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(INCLUDE) $(SHELLDRIVER)

test: $(INCLUDE) $(TESTDRIVER)
	$(CXX) $(CXXFLAGS) -o $(TEST) $(INCLUDE) $(TESTDRIVER)
	./$(TEST)

clean:
	rm -f $(EXEC) $(TEST) $(TEXT_FILES) $(INCLUDE) $(TESTDRIVER) $(SHELLDRIVER)

# Object targets
param.o:
	$(CXX) $(CXXFLAGS) -c param.cpp -o param.o

parse.o:
	$(CXX) $(CXXFLAGS) -c parse.cpp -o parse.o

myshell.o:
	$(CXX) $(CXXFLAGS) -c myshell.cpp -o myshell.o

test.o:
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o