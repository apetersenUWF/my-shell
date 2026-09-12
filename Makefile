CXX = g++

CXXFLAGS = -std=c++11 -Wall -g

OBJS = param.o main.o parse.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

param.o : param.cpp param.hpp
parse.o : parse.cpp parse.hpp param.hpp
main.o  : main.cpp test.cpp param.hpp parse.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)