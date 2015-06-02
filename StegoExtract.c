/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * StegoExtract.c: A program for decrypting images                      *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "lsbsfunctions.h"

//argv takes in an image(to decrypt) and any name for the output file(to store decryption)
int main(int argc, char *argv[])
{
	struct Buffer b = {NULL, 0, 0};
	struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
	ReadImage(argv[1],&img);       // read image file into the image buffer img

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//start reading in stuff
	char *filename = argv[1];
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//read first 16 bytes of the image(the size lf hidden file) and get their lsbs
	//get them first in chunks of 8 bytes
	//first 16 store the file size
	//printf("MADE IT HERE #1\n");
	int size_offset = 0;
	int size_bytes = 2;
	unsigned char read_size_bytes[size_bytes];
	//printf("Reading first 16 bytes from %s\n", argv[1]);
	
	if (img.iscolor)
	{
		unsigned char *red_size_array[2][8];
		arrayStorageRed(img, red_size_array, size_bytes, size_offset);
		
		getlsbs_2d(red_size_array, size_bytes, read_size_bytes);
	}	

	else
	{
		unsigned char *size_array[2][8];
		arrayStorage(img, size_array, size_bytes, size_offset);
		//printArrays(size_array, size_bytes);
		
		getlsbs_2d(size_array, size_bytes, read_size_bytes);

		// PRINTBIN(read_size_bytes[0]);
		// printf(" which equals %u\n", read_size_bytes[0]);
		// PRINTBIN(read_size_bytes[1]);
		// printf(" which equals %u", read_size_bytes[1]);
		// printf("\n");
	}
	

	unsigned short msb_size_byte = (unsigned short) read_size_bytes[0];
	unsigned short lsb_size_byte = (unsigned short) read_size_bytes[1];
	
	unsigned short combined_size_bytes = (msb_size_byte << 8) | lsb_size_byte;
	//printf("Here is the actual size hopefully? : %u\n", combined_size_bytes);	

	// int k;
	// for (k=0; k<size_bytes; k++)
	// {
	// 	//PRINTBIN(read_size_bytes[k]);
	// }
	// printf("\n");

	b.size = combined_size_bytes;
	printf("\nb.size is: %d\n", b.size);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Next 32 bytes get the files extension
	int ext_bytes = 4;
	int ext_offset = 16;
	unsigned char read_ext_bytes[ext_bytes];

	if (img.iscolor)
	{
		unsigned char *red_ext_array[4][8];
		
		arrayStorageRed(img, red_ext_array, ext_bytes, ext_offset);

		getlsbs_2d(red_ext_array, ext_bytes, read_ext_bytes);
		
	}

	else
	{
		unsigned char *ext_array[4][8];
		arrayStorage(img, ext_array, ext_bytes, ext_offset);

		getlsbs_2d(ext_array, ext_bytes, read_ext_bytes);
	}
	
	//type cast bytes into characters for printing
	//also stores the chars into a string
	char file_extension[4];
	int z;
	for (z=0; z<4; z++)
	{
		file_extension[z] = (char)read_ext_bytes[z];
	}
	printf("hidden file type = <%s>\n",file_extension+1);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Next xxxxx bytes
	//printf("MADE IT HERE #2\n");
	int payload_bytes = b.size;
	int payload_offset = 48;
	unsigned char read_payload_bytes[payload_bytes];

	if (img.iscolor)
	{
		//printf("MADE IT TO PAYLOAD EXTRACTION\n");
		// unsigned char *red_payload_array[payload_bytes][8];

		// arrayStorageRed(img, red_payload_array, payload_bytes, payload_offset);
		// getlsbs_2d(red_payload_array, payload_bytes, read_payload_bytes);

		unsigned char *red_payload_array[b.size][8];
	    unsigned char *green_payload_array[b.size][8];
	    unsigned char *blue_payload_array[b.size][8];

	    int *RGB_bytes_stored;
	   
	    RGB_bytes_stored = arrayStorageColor(img, red_payload_array, green_payload_array, blue_payload_array, payload_bytes, payload_offset);
    	// printf("FINISHED RGB STORAGE\n");
    	// printf("Made it right before setting payload lsbs\n");
	    // printf("Here is the num of payload bytes stored in red: %d\n", RGB_bytes_stored[0]);
	    // printf("Here is the num of payload bytes stored in green: %d\n", RGB_bytes_stored[1]);
	    // printf("Here is the num of payload bytes stored in blue: %d\n", RGB_bytes_stored[2]);
	    // printf("TOTAL PAYLOAD BYTES STORED: %d\n", RGB_bytes_stored[0]+RGB_bytes_stored[1]+RGB_bytes_stored[2]);
	    // printf("ACTUAL B.SIZE: %d\n", b.size);
    	
    	getlsbs_2dColor(red_payload_array, green_payload_array, blue_payload_array, read_payload_bytes, RGB_bytes_stored);
		// printf("FINISHED GETTING LSBS\n");
		b.max_size = (3*(16+32+b.size));
	}

	else
	{
		//printf("Reading next %d bytes from %s\n", payload_bytes, argv[1]);
		unsigned char *payload_array[payload_bytes][8];
		arrayStorage(img, payload_array, payload_bytes, payload_offset);
		//printArrays(payload_array, payload_bytes);

		getlsbs_2d(payload_array, payload_bytes, read_payload_bytes);
		
		b.max_size = ((16+32+b.size));
	}

	b.data = malloc(b.size*8);
	//printf("\nLSBS of next %d bytes\n", payload_bytes);
	//stores bytes into b.data
	int k;
	for (k=0; k<payload_bytes; k++)
	{
		//PRINTBIN(read_payload_bytes[k]);
		//printf("\n");
		b.data[k] = read_payload_bytes[k];
	}
	//printf("\n");

	

	WriteBinaryFile(argv[2], b);
	free(b.data);
	//printf("\nread b.size is: %d\n", size_num);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

}
