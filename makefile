all: main.cpp 
	clang++ -std=c++17 -stdlib=libc++ -o myrun main.cpp
test: main.cpp
	./myrun
clean:
	rm -rf *.o myrun
