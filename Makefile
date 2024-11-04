com:
	gcc -c ./src/*.c
	mv *.o ./obj
	gcc ./obj/*.o -o main

run:
	make com
	clear
	./main
