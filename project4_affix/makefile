target = main
source = $(wildcard *.cpp)
OBJS = $(source:%.cpp=%.o)
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror
LDFLAGS = -lncurses

$(target) : $(OBJS)
	g++ -o $(target) $(OBJS) $(LDFLAGS)
%.o:%.cpp
	g++ -c -o $@ $(CXXFLAGS) $<

clean:
	rm main *.o

