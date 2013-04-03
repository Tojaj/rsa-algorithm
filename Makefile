CC=gcc

CFLAGS= -Wall -Wextra -g -O2 -std=c99
LINKFLAGS= -lgmp

main:
	$(CC) $(CFLAGS) src/main.c src/prime.c src/keygen.c src/gcd.c src/modinvert.c src/encrypt.c src/decrypt.c $(LINKFLAGS) -o kry

clean:
	rm -f kry

