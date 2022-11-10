# Homework #1

## Contents
1. [Table of Contents](##content)
1. [Task](#task)
1. [Console application](#console application)
1. [Division of duties](#division-of-duties)
1. [Optional interface](#additional-interface)
1. [Console application](#console-application-1)
1. [Division of duties](#division-of-duties-1)

## Task.
An application `./hw-01_bmp` that cuts a rectangle out of a BMP file with an image,
rotates that rectangle 90 degrees clockwise, and saves the result to a separate
file.

All images (the original read and saved result) are stored in the specified format:

* The general format is [BMP](https://ru.wikipedia.org/wiki/BMP).
* The *DIB* format with header `BITMAPINFOHEADER` (version 3) is used within the BMP format.
* The value of the `biHeight` field (image height) is strictly greater than zero.
* 24 bits of color per pixel are used (one byte per color channel).
* Palette (color table) is not used.
* Compression is not used.

### Console Application
The application is started with the following command:

```
./hw-01_bmp crop-rotate 'in-bmp' 'out-bmp' 'x' 'y' 'w' 'h'
```

Parameters used:

* `crop-rotate` - mandatory parameter indicating the action to be performed.
* `in-bmp` - name of the input file with the image.
* `out-bmp` - name of the output file with the image.
* `x`, `y` - coordinates of the upper left corner of the area to be cut and rotated.
  The coordinates start from zero, so *(0, 0)* is the upper left corner.
* `w`, `h` are, respectively, the width and height of the area before rotation.

Thus, if we denote the width and height of the original image by `W` and `H`, respectively,
the following inequalities are true for the correct arguments:

* `0 <= x < x + w <= W`
* `0 <= y < y + h <= H`

### Divide responsibilities.
* The files `bmp.c` and `bmp.h` contain the workings of the image, namely the functions:
  1. `load_bmp` (load the image).
  1. `crop` (cut a section).
  1. `rotate` (rotate).
  1. `save_bmp` (save image).
* Argument handling and entry point are implemented in `main.c`.

## Optional interface
In addition to the `crop-rotate` command, the `insert` and `extract` commands are implemented,
which allow you to hide a message inside the image
([стеганография](https://ru.wikipedia.org/wiki/%D0%A1%D1%82%D0%B5%D0%B3%D0%B0%D0%BD%D0%BE%D0%B3%D1%80%D0%B0%D1%84%D0%B8%D1%8F)).
The `insert` command stores the message in the image, while the `extract` command extracts it from there.

### Encoding method.
The original message consists only of capital Latin letters, a space, a period, and a comma.
Each character is converted to a number from 0 to 28, respectively (29 different values in total),
and the number is converted into five bits, written from lower to higher.
A total message of `N` characters is encoded using `5N` Bits.

To transmit the message, in addition to the image-carrier, you will need a __key__ - a text file,
which describes in which pixels the bits of the message are encoded.
In this file, on separate lines are written:

* The `x` and `y` coordinates (`0 <= x < W`, `0 <= y < H`) of the pixel in which the
  the corresponding bit.
* The letter `R`/`G`/`B` denotes the color channel in whose low-order bit the
  message.

If the key writes more bits than the message needs, the last lines are ignored.

### Console application.
To save a secret line to an image, the application is started with the following command:
```
./hw-01_bmp insert 'in-bmp' 'out-bmp' 'key-txt' 'msg-txt'
```

To extract the secret string from the image, the application is started with the following command: ``:
```
./hw-01_bmp extract 'in-bmp' 'key-txt' 'msg-txt'
```

Parameters used:

* ``in-bmp`` - the name of the input image file.
* `out-bmp` - name of the output file with the image.
* `key-txt` - test file with a key.
* `msg-txt` - text file with the secret message.

This leaves all the other requirements for correctness: the `crop-rotate` command, checking arguments
and others.

### Separation of duties
The functions for steganography are implemented in separate files `stego.h`/`stego.c`.


Translated with www.DeepL.com/Translator (free version)
