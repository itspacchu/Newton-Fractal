main : newton.cpp
	g++ -o newtonr newton.cpp -lraylib
	./newtonr

mainwin : newton.cpp
	x86_64-w64-mingw32-g++ -o newton.exe newton.cpp -lraylib
