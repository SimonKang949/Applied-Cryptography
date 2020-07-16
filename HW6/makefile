hw6: main.o primes.o trialdiv.o millerrabin.o rndsearch.o maurer.o
	gcc -o hw6 main.o trialdiv.o millerrabin.o rndsearch.o maurer.o -L/home/scf-22/csci551b/openssl/lib -lcrypto -lm
main.o: main.c
	gcc -c main.c -I/home/scf-22/csci551b/openssl/include
primes.o: primes.c
	gcc -c primes.c -I/home/scf-22/csci551b/openssl/include
trialdiv.o: trialdiv.c
	gcc -c trialdiv.c -I/home/scf-22/csci551b/openssl/include
millerrabin.o: millerrabin.c
	gcc -c millerrabin.c -I/home/scf-22/csci551b/openssl/include
rndsearch.o: rndsearch.c
	gcc -c rndsearch.c -I/home/scf-22/csci551b/openssl/include
maurer.o: maurer.c
	gcc -c maurer.c -I/home/scf-22/csci551b/openssl/include
clean:
	rm hw6 *.o
