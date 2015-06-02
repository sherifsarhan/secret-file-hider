#include <stdio.h>
#include <stdlib.h>
#include "lsbsfunctions.h"
#include "image.h"

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setlsbs(unsigned char *p[], unsigned char b0)
{
	int i;
	for (i=7;i>=0;i--)
	{
		*p[i] = (*p[i] & ~1) | (b0 & 1);
		//shift byte b0 to the right
		b0 = b0>>1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setlsbsColor(unsigned char *red[], unsigned char *green[], unsigned char *blue[], unsigned char b0)
{
	int i;
	for (i=7;i>=0;i--)
	{
		*red[i] = (*red[i] & ~1) | (b0 & 1);
		*green[i] = (*green[i] & ~1) | (b0 & 1);
		*blue[i] = (*blue[i] & ~1) | (b0 & 1);
		//shift byte b0 to the right
		b0 = b0>>1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setlsbsRed(unsigned char *red[], unsigned char *green[], unsigned char *blue[], unsigned char b0)
{
	int i;
	for (i=7;i>=0;i--)
	{
		*red[i] = (*red[i] & ~1) | (b0 & 1);
		*green[i] = (*green[i] & ~1) | (b0 & 1);
		*blue[i] = (*blue[i] & ~1) | (b0 & 1);
		//shift byte b0 to the right
		b0 = b0>>1;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Gets the 8 lsbs from an 8 byte array p and stores it into byte b0
unsigned char getlsbs(unsigned char *p[])
{
	//printf("Entered getLSBS\n");
	unsigned char b0;
	int i;
	for (i=0; i<8; i++)
	{
		//printf("\nReading this byte: \n");
		//PRINTBIN(*p[i]);
		//printf("\n");
		//shifts 1 bit to the left. It's okay if the first byte of 0 is moved to the left
		//doesn't make a difference, but for all new lsbs to be stored, they need to be moved left.
		b0 = b0<<1;
		//printf("\n");
		//PRINTBIN(b0);
		//printf("\n");
		//sets b0 = (zeroed out last bit of b0) sets it to (gets lsb of p[i])
		b0 = (b0 & ~1) | (*p[i] & 1);
		//PRINTBIN(b0);
		//printf("\n");		
	}
	return b0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
unsigned char getlsbsColor(unsigned char *red[], unsigned char *green[], unsigned char *blue[])
{
	//printf("Entered getLSBS\n");
	unsigned char b0;
	int i;
	for (i=0; i<8; i++)
	{
		//printf("\nReading this byte: \n");
		//PRINTBIN(*p[i]);
		//printf("\n");
		//shifts 1 bit to the left. It's okay if the first byte of 0 is moved to the left
		//doesn't make a difference, but for all new lsbs to be stored, they need to be moved left.
		b0 = b0<<1;
		//printf("\n");
		//PRINTBIN(b0);
		//printf("\n");
		//sets b0 = (zeroed out last bit of b0) sets it to (gets lsb of p[i])
		b0 = (b0 & ~1) | (*red[i] & 1);
		b0 = (b0 & ~1) | (*green[i] & 1);
		b0 = (b0 & ~1) | (*blue[i] & 1);
		//PRINTBIN(b0);
		//printf("\n");		
	}
	return b0;
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//takes a pointer to an array p of bytes and how many bytes need to be printed
void printBytes(unsigned char *p[], int num)
{
	int i;
	for (i=0;i<num;i++)
	{
		//print binary
		PRINTBIN(*p[i]);
		printf(" ");
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//takes in an image struct to access the bytes from image
//takes in an array of bytes (unsigned chars) to store the bytes
//stores 8 bytes into an array
//x is the offset to start storing from
//example: store the first eight bytes by setting x to 0
//example: store the second eight bytes by setting x to 8
void storeBytes(struct Image img, unsigned char *byteArray[], int offset)
{
	int z;
	for (z=0; z<8; z++)
	{
		//stores 8 bytes from the image starting at the offset
		//byteArray[z] = (unsigned char)img.gray[z+offset];
		//try this out?
		byteArray[z] = &img.gray[z+offset];
	}
}
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void storeBytesRed(struct Image img, unsigned char *red_byteArray[], int offset)
{
	int z;
	for (z=0; z<8; z++)
	{
		//stores 8 bytes from the image starting at the offset
		//byteArray[z] = (unsigned char)img.gray[z+offset];
		//try this out?
		red_byteArray[z] = &img.red[z+offset];
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void storeBytesGreen(struct Image img, unsigned char *green_byteArray[], int offset)
{
	int z;
	for (z=0; z<8; z++)
	{
		//stores 8 bytes from the image starting at the offset
		//byteArray[z] = (unsigned char)img.gray[z+offset];
		//try this out?
		green_byteArray[z] = &img.green[z+offset];
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void storeBytesBlue(struct Image img, unsigned char *blue_byteArray[], int offset)
{
	int z;
	for (z=0; z<8; z++)
	{
		//stores 8 bytes from the image starting at the offset
		//byteArray[z] = (unsigned char)img.gray[z+offset];
		//try this out?
		blue_byteArray[z] = &img.blue[z+offset];
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//is a tool to store byte arrays into 2-dimensional arrays
//takes in an image structure, a 2-d array of image bytes, how many byte arrays of size 8 need to be stored, and an offset
//offset tells the storeBytes function where to start assigning bytes for each array
void arrayStorage(struct Image img, unsigned char *p[][8], int num_byteArrays, int offset)
{
	//stores image bytes to their respective arrays 
	int k;
	for (k=0; k<num_byteArrays; k++)
	{
		storeBytes(img, p[k], offset);
		//offset changes by 8 every time because 8 bytes are taken from the image to be stored in one of the byteArrays
		offset += 8;
	}

}
// //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
int* arrayStorageColor(struct Image img, unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], int num_byteArrays, int red_offset)
{
    //printf("Made it into arrayStorageColor\n");
	//stores image bytes to their respective arrays 
	int k;
	int red_bytes_stored = 0;
	int *RGB_bytes_stored = malloc(sizeof(int)*3);
	for (k=0; k<num_byteArrays; k++)
	{
		//printf("I need to store %d in RED\n", num_byteArrays);
		//printf("Red offset is currently: %d\n", red_offset);
		//printf("Available Red bytes are: %d\n", (img.NofR*img.NofC));
		if (((img.NofR*img.NofC) - red_offset) < 8)
		{
			//printf("Ran out of room in RED\n");
			int green_offset = 0;
			arrayStorageGreen(img, green, num_byteArrays-red_bytes_stored, green_offset, RGB_bytes_stored, blue);
			break;
		}

		else
		{
			storeBytesRed(img, red[k], red_offset);
			// printf("Just stored a byte in RED payload\n");
			// printf("Red payload bytes: %d\n", red_bytes_stored);
			//offset changes by 8 every time because 8 bytes are taken from the image to be stored in one of the byteArrays
			red_offset += 8;
			red_bytes_stored++;
		}
		
	}
	RGB_bytes_stored[0] = red_bytes_stored;
	return RGB_bytes_stored;

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void arrayStorageRed(struct Image img, unsigned char *red[][8], int num_byteArrays, int offset)
{
	//stores image bytes to their respective arrays 
	int k;
	for (k=0; k<num_byteArrays; k++)
	{
		// if (((img.NofR*img.NofC) - offset) == 0)
		// {
		// 	int green_offset = 0;
		// 	//unsigned char *connect_RGB[];
		// 	unsigned char *green[num_byteArrays][8];
		// 	arrayStorageGreen(img, green, k, green_offset);
		// 	//return connect_RGB;
		// }

		storeBytesRed(img, red[k], offset);
		//offset changes by 8 every time because 8 bytes are taken from the image to be stored in one of the byteArrays
		offset += 8;
	}

}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void arrayStorageGreen(struct Image img, unsigned char *green[][8], int num_byteArrays_green, int green_offset, int* RGB_bytes_stored, unsigned char *blue[][8])
{
	//printf("Made it into arrayStorageGreen\n");
	//stores image bytes to their respective arrays 
	int k;
	int green_bytes_stored = 0;
	for (k=0; k<num_byteArrays_green; k++)
	{
		//printf("Green offset is currently: %d\n", green_offset);
		//printf("Available Green bytes are: %d\n", (img.NofR*img.NofC));
		if (((img.NofR*img.NofC) - green_offset) < 8)
		{
			//printf("Ran out of room in GREEN\n");
			int blue_offset = 0;
			arrayStorageBlue(img, blue, num_byteArrays_green-green_bytes_stored, blue_offset, RGB_bytes_stored);
			break;
		}

		else
		{
			storeBytesGreen(img, green[k], green_offset);

			//offset changes by 8 every time because 8 bytes are taken from the image to be stored in one of the byteArrays
			green_offset += 8;
			green_bytes_stored++;
		}
		
	}
	//printf("Finished storing green bytes\n");
	//printf("Green bytes stored: %d\n", green_bytes_stored);
	RGB_bytes_stored[1] = green_bytes_stored;
	//printf("Stored number of green bytes stored into RGB_bytes_stored Array\n");
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void arrayStorageBlue(struct Image img, unsigned char *blue[][8], int num_byteArrays, int blue_offset, int* RGB_bytes_stored)
{
	//printf("ENTERED BLUE STORAGE\n");
	//stores image bytes to their respective arrays 
	int k;
	int blue_bytes_stored = 0;
	for (k=0; k<num_byteArrays; k++)
	{	
		//printf("Blue offset is currently: %d\n", blue_offset);
		//printf("Available Blue bytes are: %d\n", (img.NofR*img.NofC));
		//printf("Blue offset is currently: %d\n", blue_offset);
		storeBytesBlue(img, blue[k], blue_offset);
		//offset changes by 8 every time because 8 bytes are taken from the image to be stored in one of the byteArrays
		blue_offset += 8;
		blue_bytes_stored++;
	}
	RGB_bytes_stored[2]=blue_bytes_stored;
	//printf("Blue bytes stored: %d\n", blue_bytes_stored);
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//prints out 2-d array (p[][]) that have byte arrays (of size 8) in them
void printArrays(unsigned char *p[][8], int num_byteArrays)
{
	int dummy_count = 0;
	int k;
	for (k=0; k<num_byteArrays; k++)
	{
		printBytes(p[k], 8);
		if (dummy_count==1)
		{
			printf("\n");
			dummy_count = 0;
		}
		else
		{
			dummy_count++;
		}
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//sets lsbs for 2-d array (p[][]) that have byte arrays (of size 8) in them
//takes in an array of however many secret bytes need to be hidden in the lsbs of each of the arrays
void setlsbs_2d(unsigned char *p[][8], int num_byteArrays, unsigned char *secret_bytes)
{	
	int k;
	for (k=0; k<num_byteArrays; k++)
	{
		setlsbs(p[k], secret_bytes[k]);
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void setlsbs_2dColor(unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], unsigned char *secret_bytes, int *RGB_bytes_stored)
{
	int i,j,k;
	int z = 0;
	for (i=0; i<RGB_bytes_stored[0]; i++)
	{
		setlsbs(red[i], secret_bytes[z]);
		z++;
	}
	for (j=0; j<RGB_bytes_stored[1]; j++)
	{
		setlsbs(green[j], secret_bytes[z]);
		z++;
	}
	for (k=0; k<RGB_bytes_stored[2]; k++)
	{
		setlsbs(blue[k], secret_bytes[z]);
		z++;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//gets lsbs from 2d array of image bytes and returns it into an array of however many bytes there may be
void getlsbs_2d(unsigned char *p[][8], int num_bytes, unsigned char read_bytes[])
{	
	int k;
	for (k=0; k<num_bytes; k++)
	{ 
		read_bytes[k] = getlsbs(p[k]);
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
void getlsbs_2dColor(unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], unsigned char read_bytes[], int *RGB_bytes_stored)
{
	int i,j,k;
	int z = 0;
	for (i=0; i<RGB_bytes_stored[0]; i++)
	{
		read_bytes[z] = getlsbs(red[i]);
		z++;
	}
	for (j=0; j<RGB_bytes_stored[1]; j++)
	{
		read_bytes[z] = getlsbs(green[j]);
		z++;
	}
	for (k=0; k<RGB_bytes_stored[2]; k++)
	{
		read_bytes[z] = getlsbs(blue[k]);
		z++;
	}
}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
