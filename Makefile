objects = cliente.o

build: main.c $(objects)
	gcc -Wall main.c $(objects) -o app

clean:
	rm -rf $(objects)

cliente.o: cliente.c cliente.h
	gcc -c cliente.c
