CXX = g++

CXXFLAGS = -std=c++11 -Wall

OBJS = param.o main.o

EXEC = run

TEXT_FILES =

run: $(OBJS)
				$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

param.o : param.hpp
main.o : param.hpp

clean :
				rm -f $(EXEC) $(TEXT_FILES) $(OBJS)