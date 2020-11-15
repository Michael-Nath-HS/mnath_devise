random.out: main.o
	touch out.out
	gcc -o random.out main.o
main.o: main.c
	gcc -c main.c
run: random.out
	./random.out
clean:
	rm ./*o
	rm ./*out