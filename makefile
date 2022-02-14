main : newton.cpp
	g++ -o ./build/newton newton.cpp -lraylib -lpthread -lm
	./build/newton
	rm ./build/newton

