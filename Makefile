all: app.exe

app.exe: main.o
	g++ -LC:\SFML-2.5.1\lib -o app.exe main.o -lmingw32 -luser32 -lgdi32 -lwinmm -ldxguid -lsfml-graphics-d -lsfml-window-d -lsfml-system-d

main.o: main.cpp
	g++ -Wall -g -IC:\SFML-2.5.1\include -c main.cpp -o main.o

clean:
	rm -f main.o app.exe
