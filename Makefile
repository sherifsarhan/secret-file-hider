all: Stego StegoExtract

Stego:
	gcc image.c -c
	gcc Stego.c -c
	gcc lsbsfunctions.c -c
	gcc -g Stego.o image.o lsbsfunctions.o -o Stego

StegoExtract:
	gcc image.c -c
	gcc StegoExtract.c -c
	gcc lsbsfunctions.c -c
	gcc StegoExtract.o image.o lsbsfunctions.o -o StegoExtract

clean:
	rm -f *.o Stego StegoExtract