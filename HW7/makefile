hw7: main.o rc4.o x1.o x2.o x3.o x4.o x5.o
	gcc -o hw7 main.o rc4.o x1.o x2.o x3.o x4.o x5.o -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm
main.o: main.c
	gcc -c main.c
rc4.o: rc4.c
	gcc -c rc4.c -I/home/scf-22/csci551b/openssl/include
x1.o: x1.c
	gcc -c x1.c
x2.o: x2.c
        gcc -c x2.c
x3.o: x3.c
        gcc -c x3.c
x4.o: x4.c
        gcc -c x4.c
x5.o: x5.c
        gcc -c x5.c

clean:
	rm hw7 *.o *.temp *.states *.rc4 *.x1 *.x2 *.x3 *.x4 *.x5

