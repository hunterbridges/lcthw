CFLAGS=-DNDEBUG -Wall -g

all: ex19

ex19: object.o engine.o

ex19alt: object.o engine.o

test:
	make clean ex19
	chmod +x ex19test.sh
	./ex19test.sh

clean:
	rm -f ex19 ex19alt object.o engine.o
