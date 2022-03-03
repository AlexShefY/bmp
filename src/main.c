#include <string.h>
#include "bmp.h"
#include "stego.h"

static void crop_rotate(myBmp* bmpIn, myBmp* bmpOut, int argc, char *argv[]) {
  if (argc < 8) {
    printf("Wrong arguments");
    clean(bmpIn);
    clean(bmpOut);
    exit(1);
  }
  int x = atoi(argv[4]);
  int y = atoi(argv[5]);
  int w = atoi(argv[6]);
  int h = atoi(argv[7]);
  if (y + h > bmpIn->header.Height || x + w > bmpIn->header.Width) {
    printf("Wrong dimensions");
    clean(bmpIn);
    clean(bmpOut);
    exit(1);
  }
  myBmp *newbmp = malloc(sizeof(myBmp));
  if (newbmp == NULL) {
    printf("Error");
    clean(bmpIn);
    clean(bmpOut);
    exit(1);
  }
  if (crop(bmpIn, newbmp, x, h, y, w)) {
    clean(newbmp);
    clean(bmpIn);
    clean(bmpOut);
    printf("Can not create a table");
    exit(1);
  }
  if (rotate(newbmp, bmpOut)) {
    clean(newbmp);
    clean(bmpIn);
    clean(bmpOut);
    printf("Can not create a table");
    exit(1);
  }
  clean(newbmp);
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    printf("Wrong arguments");
    exit(1);
  }
  FILE *in = fopen(argv[2], "rb");
  if (in == NULL) {
    printf("Error");
    exit(1);
  }
  myBmp *bmp = malloc(sizeof(myBmp));
  if (bmp == NULL) {
    printf("Error");
    fclose(in);
    exit(1);
  }
  if (load_bmp(bmp, in)) {
    clean(bmp);
    fclose(in);
    printf("Error");
    exit(1);
  }
  fclose(in);
  if (strcmp(argv[1], "crop-rotate") == 0) {
    myBmp *newbmp1 = malloc(sizeof(myBmp));
    if (newbmp1 == NULL) {
      printf("Error");
      clean(bmp);
      exit(1);
    }
    crop_rotate(bmp, newbmp1, argc, argv);
    FILE *out = fopen(argv[3], "wb");
    save_bmp(newbmp1, out); 
    clean(newbmp1);
    fclose(out);
  }
  else if (strcmp(argv[1], "insert") == 0) {
    if (argc < 6) {
      printf("Wrong arguments");
      clean(bmp);
      exit(1);
    }
    FILE *key = fopen(argv[4], "rt");
    FILE *msg = fopen(argv[5], "rt");
    insert(bmp, key, msg);
    FILE *out = fopen(argv[3], "wb");
    save_bmp(bmp, out);
    fclose(out);
    fclose(key);
    fclose(msg);
  }
  else if (strcmp(argv[1], "extract") == 0) {
    if (argc < 5) {
      printf("Wrong arguments");
      clean(bmp);
      exit(1);
    }
    FILE *key = fopen(argv[3], "rt");
    FILE *msg = fopen(argv[4], "wt");
    extract(bmp, key, msg);
    fclose(msg);
    fclose(key);
  }
  else {
    printf("Wrong arguments");
    clean(bmp);
    exit(1);
  }
  clean(bmp);
  return 0;
}
