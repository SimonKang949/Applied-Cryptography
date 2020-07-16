hw5: main.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o
	gcc -o hw5 main.o tablecheck.o modprod.o keyexpand.o encrypt.o decrypt.o inverse.o
main.o: main.c
	gcc -c main.c
tablecheck.o: tablecheck.c
	gcc -c tablecheck.c
modprod.o: modprod.c
	gcc -c modprod.c
keyexpand.o: keyexpand.c
	gcc -c keyexpand.c
encrypt.o: encrypt.c
	gcc -c encrypt.c
decrypt.o: decrypt.c
	gcc -c decrypt.c
inverse.o: inverse.c
	gcc -c inverse.c
clean:
	rm hw5 *.o
