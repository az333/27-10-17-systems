all: rand.c 
	gcc -o "rando" rand.c
run: all
	./rando
