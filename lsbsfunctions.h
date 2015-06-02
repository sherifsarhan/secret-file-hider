#include <stdio.h>
#include <stdlib.h>
#include "image.h"

#define BYTETOBINARYPATTERN "%d%d%d%d%d%d%d%d"

#define BYTETOBINARY(byte)  \
  (byte & 0x80 ? 1 : 0), \
  (byte & 0x40 ? 1 : 0), \
  (byte & 0x20 ? 1 : 0), \
  (byte & 0x10 ? 1 : 0), \
  (byte & 0x08 ? 1 : 0), \
  (byte & 0x04 ? 1 : 0), \
  (byte & 0x02 ? 1 : 0), \
  (byte & 0x01 ? 1 : 0)

#define PRINTBIN(x) printf(BYTETOBINARYPATTERN, BYTETOBINARY(x));

void setlsbs(unsigned char *p[], unsigned char b0);
void setlsbsColor(unsigned char *red[], unsigned char *green[], unsigned char *blue[], unsigned char b0);
unsigned char getlsbs(unsigned char *p[]);
unsigned char getlsbsColor(unsigned char *red[], unsigned char *green[], unsigned char *blue[]);
void printBytes(unsigned char *p[], int num);
void storeBytes(struct Image img, unsigned char *byteArray[], int offset);
void storeBytesRed(struct Image img, unsigned char *red_byteArray[], int offset);
void storeBytesGreen(struct Image img, unsigned char *green_byteArray[], int offset);
void storeBytesBlue(struct Image img, unsigned char *blue_byteArray[], int offset);
void arrayStorage(struct Image img, unsigned char *p[][8], int num_byteArrays, int offset);
int* arrayStorageColor(struct Image img, unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], int num_byteArrays, int red_offset);
void arrayStorageRed(struct Image img, unsigned char *red[][8], int num_byteArrays, int offset);
void arrayStorageGreen(struct Image img, unsigned char *green[][8], int num_byteArrays, int green_offset, int* RGB_bytes_stored, unsigned char *blue[][8]);
void arrayStorageBlue(struct Image img, unsigned char *blue[][8], int num_byteArrays, int blue_offset, int* RGB_bytes_stored);
void printArrays(unsigned char *p[][8], int num_byteArrays);
void setlsbs_2d(unsigned char *p[][8], int num_byteArrays, unsigned char *secret_bytes);
void setlsbs_2dColor(unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], unsigned char *secret_bytes, int *RGB_bytes_stored);
void getlsbs_2d(unsigned char *p[][8], int num_bytes, unsigned char read_bytes[]);
void getlsbs_2dColor(unsigned char *red[][8], unsigned char *green[][8], unsigned char *blue[][8], unsigned char *read_bytes, int *RGB_bytes_stored);