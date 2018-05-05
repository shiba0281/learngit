main:main.o add.o hello.o
	g++ -o main main.o add.o hello.o
main.o: main.cpp main.h
	g++ -c -o main.o main.cpp
add.o: add.cpp main.h
	g++ -c -o add.o add.cpp
hello.o: hello.cpp main.h
	g++ -c -o hello.o hello.cpp
clean:
	rm main *.o
