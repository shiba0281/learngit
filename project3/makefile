target = main
source = $(wildcard *.cpp)
OBJS = $(source:%.cpp=%.o)
CXXFLAGS = -std=c++17 -Wall -Wextra -Werror

$(target) : $(OBJS)
	g++ -o $(target) $(OBJS)
%.o:%.cpp
	g++ -c -o $@ $(CXXFLAGS) $<

clean:
	rm main *.o

