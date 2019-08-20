
CFLAGS = -g -Wall -DFUSE_USE_VERSION=26 `pkg-config fuse --cflags`
LINKFLAGS = -Wall `pkg-config fuse --libs`

all: bin/fs

clean:
	rm -rf bin obj

bin: 
	mkdir -p bin

bin/fs: bin obj/fs.o obj/device.o obj/main.o
	g++ -g -o bin/fs obj/* $(LINKFLAGS)

obj:
	mkdir -p obj

obj/main.o: obj main.c fs.h
	gcc -g $(CFLAGS) -c main.c -o $@

obj/fs.o: obj fs.c fs.h 
	g++ -g $(CFLAGS) -c fs.c -o $@

obj/device.o: obj device.c device.h
	g++ -g $(CFLAGS) -c device.c -o $@