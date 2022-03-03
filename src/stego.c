#include "stego.h"


static int8_t* get_color(RGB* point, char color) {
  switch (color) {
    case 'R' :
      return &point->red;
    case 'G' :
      return &point->green;
    default :
      return &point->blue;
  }
}

void insert(myBmp *bmpIn, void *key, void *msg) {
  char c;
  while (fscanf(msg, "%c", &c) == 1) {
    int code;
    switch (c) {
      case ' ' :
        code = 26;
        break;
      case '.' :
        code = 27;
        break;
      case ',' :
        code = 28;
        break;
      case '\n' :
        code = -1;
        break;
      default : 
        code = c - 'A';
        break;
    }
    if (code == -1) {
      break;
    }
    for (int i = 0; i < 5; i++) {
      int x, y;
      char color;
      if (fscanf(key, "%d %d %c", &x, &y, &color) != 3) {
        printf("Wrong key arguments");
        exit(1);
      }
      y = bmpIn->header.Height - 1 - y;
      int8_t* pointer = get_color(&bmpIn->table[y][x], color);
      *pointer -= *pointer & 1; 
      *pointer += code & 1;
      code /= 2;
    }
  }
}

void extract(myBmp *bmpIn, void *key, void *msg) {
  int x, y;
  char color;
  char result;
  int code;
  while (fscanf(key, "%d %d %c", &x, &y, &color) == 3) {
    code = 0;
    y = bmpIn->header.Height - 1 - y;
    code += *get_color(&bmpIn->table[y][x], color) & 1;
    for (int i = 1; i < 5; i++) {
      if (fscanf(key, "%d %d %c", &x, &y, &color) != 3) {
        printf("Wrong key arguments");
        exit(1);
      }
      y = bmpIn->header.Height - 1 - y;
      int8_t* pointer = get_color(&bmpIn->table[y][x], color);
      code += (*pointer & 1) * (1 << i);
    }
    switch (code) {
      case 26 :
        result = ' ';
        break;
      case 27 :
        result = '.';
        break;
      case 28 :
        result = ',';
        break;
      default :
        result = code + 'A';
        break;
    }
    fprintf(msg, "%c", result);
  }
  fprintf(msg, "\n");
}
