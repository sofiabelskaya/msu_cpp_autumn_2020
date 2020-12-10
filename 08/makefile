all: main.cpp 
	clang++ -std=c++17 -stdlib=libc++ -pthread -o myrun main.cpp
test: main.cpp
	./myrun
clean:
	rm -rf *.o myrun
