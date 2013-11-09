OBJS=main.o tt.se.o
main:$(OBJS)
	g++ -std=c++0x -g -o main $^ -I../../include -lprotobuf -lprotobuf-lite
main.o:main.cpp
	g++ -std=c++0x -g -c -o $@ $^ -I../../include
tt.se.o:tt.h.se.cpp
	g++ -std=c++0x -g -c -o $@ $^ -I../../include

clean:
	rm -r *.o main
