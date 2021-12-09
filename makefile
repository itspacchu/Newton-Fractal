main : newton.cpp
	g++ -I /usr/include/eigen3/  -o newtonr newton.cpp -lraylib -lpthread
	./newtonr

