/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*
 * Stego.c: A program for manipulating images                           *
 *++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "image.h"
#include "lsbsfunctions.h"

int main(int argc, char *argv[])
{
  int i, j, k, cover_bits, bits;
  struct Buffer b = {NULL, 0, 0};
  struct Image img = {0, NULL, NULL, NULL, NULL, 0, 0};
  char *s;
  byte b0;
   
  if (argc != 4) 
    {
      printf("\n%s <cover_file> <stego_file> <file_to_hide> \n", argv[0]);
      exit(1);
    }
  ReadImage(argv[1],&img);       // read image file into the image buffer img
                                 // the image is an array of unsigned chars (bytes) of NofR rows
                                 // NofC columns, it should be accessed using provided macros
  ReadBinaryFile(argv[3],&b);    // Read binary data
 
  s = strchr(argv[3],(int)'.');
  if (strlen(s)!=4) s = ".txt";
  printf("hidden file type = <%s>\n",s+1);

  // hidden information 
  // first two bytes is the size of the hidden file
  // next 4 bytes is the extension (3 letters & \0)
  if (!GetColor)
    cover_bits = img.NofC*img.NofR;
  else 
    cover_bits = 3*img.NofC*img.NofR;    
  bits = (6+b.size)*8;
  if (bits > cover_bits)
    {
      printf("Cover file is not large enough %d (bits) > %d (cover_bits)\n",bits,cover_bits);
      exit(1);
    }
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //print out separator between byte chunks
  //printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //LSBs of first 16 bytes to be used for b.size
  //embed two size bytes
  //get second to last byte of b.size
  int size_offset = 0;
  int num_sizeBytes = 2;

  printf("\nb.size is: %d\n", b.size);

  unsigned char size_before_lastByte = (b.size >> (8*1)) & 0xFF;
  unsigned char size_lastByte = (b.size >> (8*0)) & 0xFF;
  
  unsigned char size_bytes[] = {size_before_lastByte, size_lastByte};
  
  if (img.iscolor)
  {
    unsigned char *red_size_array[2][8];

    arrayStorageRed(img, red_size_array, num_sizeBytes, size_offset);

    setlsbs_2d(red_size_array, num_sizeBytes, size_bytes);

    // printf("FINISHED STORING SIZE IN RED\n");
    // printf("The buffer size is: %d\n", b.size);
  }

  else
  {    
    unsigned char *size_array[2][8];

    //Pointing array to bytes from image..................
    arrayStorage(img, size_array, num_sizeBytes, size_offset);

    //Printing before hiding...........
    //printf("First 16 bytes before hiding..........\n");
    //printArrays(size_array, num_sizeBytes);
      
    //Setting lsbs for 2d array.....................
    setlsbs_2d(size_array, num_sizeBytes, size_bytes);

    //printf("\nb.size is: %d\n", b.size);

    //Printing after hiding............
    //printf("\nFirst 16 bytes after hiding..........\n");
    //printArrays(size_array, num_sizeBytes);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }
  

  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //print out separator between byte chunks
  //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //LSBs of next 32 to be used for 4 file extension characters
  int ext_offset = 16;
  int num_extBytes = 4;

  unsigned char ext_bytes[] = {s[0],s[1],s[2],s[3]};
  
  if (img.iscolor)
  {
    unsigned char *red_extension_array[4][8];

    arrayStorageRed(img, red_extension_array, num_extBytes, ext_offset);
    setlsbs_2d(red_extension_array, num_extBytes, ext_bytes);
    //printf("FINISHED EXTENSION SIZE IN RED\n");
  }

  else
  {
    unsigned char *extension_array[4][8];

    //Pointing array to bytes from image..................
    arrayStorage(img, extension_array, num_extBytes, ext_offset);

    //Printing before hiding.........
    //printf("Next 32 bytes before hiding..........\n");
    //printArrays(extension_array, num_extBytes);

    //Setting lsbs for 2d array.....................
    setlsbs_2d(extension_array, num_extBytes, ext_bytes);

    //Printing after hiding...........
    //printf("\nNext 32 bytes after hiding..........\n");
    //printArrays(extension_array, num_extBytes);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }



  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //print out separator between byte chunks
  //printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~");
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //next xxxxx bytes for unknown payload to be used to store payload data
  int payload_bytesNeeded = (8*b.size);
  
  int num_payloadBytes = b.size;
  int payload_offset = 48;

  if (img.iscolor)
  {
    unsigned char *red_payload_array[b.size][8];
    unsigned char *green_payload_array[b.size][8];
    unsigned char *blue_payload_array[b.size][8];

    int *RGB_bytes_stored;
    // printf("Made it right before storing bytes in RGB\n");
    RGB_bytes_stored = arrayStorageColor(img, red_payload_array, green_payload_array, blue_payload_array, num_payloadBytes, payload_offset);
    // printf("Made it right before setting payload lsbs\n");
    // printf("Here is the num of payload bytes stored in red: %d\n", RGB_bytes_stored[0]);
    // printf("Here is the num of payload bytes stored in green: %d\n", RGB_bytes_stored[1]);
    // printf("Here is the num of payload bytes stored in blue: %d\n", RGB_bytes_stored[2]);
    // printf("TOTAL PAYLOAD BYTES STORED: %d\n", RGB_bytes_stored[0]+RGB_bytes_stored[1]+RGB_bytes_stored[2]);
    // printf("ACTUAL B.SIZE: %d\n", b.size);

    //print out red payload array bytes before setting lsbs
    //printArrays(red_payload_array, RGB_bytes_stored[0]);

    //print out green payload array bytes before setting lsbs
    //printArrays(green_payload_array, RGB_bytes_stored[1]);

    //print out blue payload array bytes before setting lsbs
    //printArrays(blue_payload_array, RGB_bytes_stored[2]);

    setlsbs_2dColor(red_payload_array, green_payload_array, blue_payload_array, b.data, RGB_bytes_stored);
    
    //print out red payload array bytes after setting lsbs
    //printArrays(red_payload_array, RGB_bytes_stored[0]);

    //print out green payload array bytes after setting lsbs
    //printArrays(green_payload_array, RGB_bytes_stored[1]);

    //print out blue payload array bytes after setting lsbs
    //printArrays(blue_payload_array, RGB_bytes_stored[2]);
  }
  
  else
  {
    unsigned char *payload_array[b.size][8];
    //b.data is your unsigned char *xxxxx_array[]

    //Pointing array to bytes from image..................
    arrayStorage(img, payload_array, num_payloadBytes, payload_offset);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    //printf("\nHere are next %d bytes before hiding..........\n", payload_bytesNeeded);
    //printArrays(payload_array, num_payloadBytes);

    //Setting lsbs for 2d array.....................
    setlsbs_2d(payload_array, num_payloadBytes, b.data);

    //printf("\n\nHere are next %d bytes after hiding..........\n", payload_bytesNeeded);
    //printArrays(payload_array, num_payloadBytes);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  }
  


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  //print out separator between byte chunks
  //printf("\n~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
  WriteImage(argv[2],img);  // output stego file (cover_file + file_to_hide)
  //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
}
