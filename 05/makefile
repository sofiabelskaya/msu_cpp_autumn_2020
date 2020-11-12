all: main.cpp Serializer_deserialiser.cpp
	clang++ -std=c++17 -stdlib=libc++ -o myrun main.cpp Serializer_deserialiser.cpp
test: main.cpp Serializer_deserialiser.cpp
	./myrun
clean:
	rm -rf *.o myrun
