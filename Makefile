CC=gcc

CFLAGS= -Wall -Wextra -g -O2 -std=c99
LINKFLAGS= -lgmp
FILES = src/main.c \
	src/prime.c \
	src/keygen.c \
	src/gcd.c \
	src/modinvert.c \
	src/encrypt.c \
	src/decrypt.c \
	src/powm.c

main:
	$(CC) $(CFLAGS) $(FILES)  $(LINKFLAGS) -o kry

clean:
	rm -f kry

