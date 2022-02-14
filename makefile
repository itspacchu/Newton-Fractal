main : newton.cpp
	g++ -o ./build/newton newton.cpp -lraylib -lpthread
	./build/newton
	rm ./build/newton

