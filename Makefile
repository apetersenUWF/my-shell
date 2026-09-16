CXX = g++
CXXFLAGS = -std=c++17 -Wall -g

# Object file names
MAINDRIVER = main.o
TESTDRIVER = test.o
SHELLDRIVER = shell.o
INCLUDE = param.o parse.o

# Executable file names
EXEC = run
TEST = test
SHELL_EXEC = shell

TEXT_FILES =

# Main targets
run: $(INCLUDE) $(MAINDRIVER)
	$(CXX) $(CXXFLAGS) -o $@ $(INCLUDE) $(MAINDRIVER)

test: $(INCLUDE) $(TESTDRIVER)
	$(CXX) $(CXXFLAGS) -o $@ $(INCLUDE) $(TESTDRIVER)
	./$(TEST)

shell: $(INCLUDE) $(SHELLDRIVER)
	$(CXX) $(CXXFLAGS) -o $@ $(INCLUDE) $(SHELLDRIVER)

clean:
	rm -f $(EXEC) $(TEST) $(SHELL_EXEC) $(TEXT_FILES) $(INCLUDE) $(MAINDRIVER) $(TESTDRIVER) $(SHELLDRIVER)

# Object targets
param.o:
	$(CXX) $(CXXFLAGS) -c param.cpp -o param.o

parse.o:
	$(CXX) $(CXXFLAGS) -c parse.cpp -o parse.o

main.o:
	$(CXX) $(CXXFLAGS) -c main.cpp -o main.o

test.o:
	$(CXX) $(CXXFLAGS) -c test.cpp -o test.o

shell.o:
	$(CXX) $(CXXFLAGS) -c myshell.cpp -o shell.o