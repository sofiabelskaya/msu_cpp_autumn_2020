all: main.cpp format.cpp
	clang++ -std=c++17 -stdlib=libc++ -o myrun main.cpp format.cpp
test: main.cpp format.cpp
	./myrun
clean:
	rm -rf *.o myrun
