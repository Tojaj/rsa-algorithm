CC=gcc

CFLAGS= -Wall -Wextra -g -std=c99 -O3 -I./msieve-1.51/include/
LINKFLAGS= -lgmp -L./msieve-1.51/ -lmsieve -lm -lpthread \
	   `pkg-config zlib --libs` -ldl
FILES = src/main.c \
	src/prime.c \
	src/keygen.c \
	src/gcd.c \
	src/modinvert.c \
	src/encrypt.c \
	src/decrypt.c \
	src/powm.c \
	src/factorization.c

TARBALL=xmlcoc06.tar.gz

all: msieve kry

msieve:
	cd msieve-1.51/ && make all && cd ..

kry:
	$(CC) $(CFLAGS) $(FILES)  $(LINKFLAGS) -o kry

clean:
	rm -f kry
	cd msieve-1.51/ && make clean

release:
	rm -f $(TARBALL) && git archive --format=tar HEAD | gzip > $(TARBALL)
