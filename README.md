# secret-file-hider
This program hides any file into a PPM or PGM image.
The image will look near identical, yet will contain the contents of the secret file to later be extracted.

The process used for this steganographic process is the method of "least significant bit."
When an image parameter is given, its data is read in a binary format into byte snippets in a large array.
When the secret file parameter is given to be hidden, the program takes each individual bit and stores it
into the least significant bit of the following byte snippets of the image.

The reason that the image looks nearly identical is because each 24-bit RGB pixel of the image contains three bytes:
one red, one green, and one blue to determine the color combination of the pixel. For example, when the least
significant bit of the red byte of the pixel is altered, the color value(shade of red) is only changed by +-1 at most.
Since each byte allows for a 255 different shade values, a +-1 alteration in the shade is very miniscule and unnoticable.
In some cases the shade value stays the same because the image already had a 1 or 0 stored in it's LSB.

When the secret file is extracted from the image, the LSB's are read and combined for the binary formulation
of the secret file.

In order of all of this to be possible, bitwise operations were necessary.

Credit goes to Professor Zoran Duric for his functions to allow for PPM/PGM image manipulations.
