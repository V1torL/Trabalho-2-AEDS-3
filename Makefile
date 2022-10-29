tp2: main.c arquivo.o povos.o tempo.o
	gcc main.c arquivo.o povos.o tempo.o -o tp2

arquivo.o: arquivo.h arquivo.c
	gcc -c arquivo.c

povos.o: povos.h povos.c
	gcc -c povos.c

tempo.o: tempo.c tempo.h
	gcc -c tempo.c

clean:
	rm -rf arquivo.o povos.o tp2