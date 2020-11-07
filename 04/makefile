all: test.cpp BigInt.cpp
	clang++ -std=c++17 -stdlib=libc++ -o test1 test.cpp BigInt.cpp
test: test.cpp BigInt.cpp
	./test1
clean:
	rm -rf *.o test1
