#include "bmp.h"
#include <assert.h>

void clean(myBmp* bmp) {
  if (bmp->table) {
    for (int i = 0; i < bmp->header.Height; i++) {
      free(bmp->table[i]);
    }
  }
  free(bmp->table);
  free(bmp);
}

int load_bmp(myBmp* bmp, void *file) {
  fread(&bmp->header, sizeof(BITMAPINFOHEADER), 1, file);
  bmp->table = (RGB**)malloc(bmp->header.Height * sizeof(RGB*));
  if (bmp->table == NULL) {
    return 1;
  }
  int padding = (4 - bmp->header.Width * 3 % 4) % 4;
  for (int i = 0; i < bmp->header.Height; i++) {
    bmp->table[i] = (RGB*) malloc(bmp->header.Width * sizeof(RGB));
    if (bmp->table[i] == NULL) {
      return 1;
    }
    fread(bmp->table[i], bmp->header.Width * sizeof(RGB), 1, file);
    fseek(file, padding, SEEK_CUR);
  }
  return 0;
}

int crop(myBmp* bmp, myBmp* newbmp, int x, int h, int y, int w) {
  newbmp->header = bmp->header;
  newbmp->header.Height = h;
  newbmp->header.Width = w;
  y = bmp->header.Height - y - 1 - (h - 1);
  newbmp->table = (RGB**)malloc(newbmp->header.Height * sizeof(RGB*));
  if (newbmp->table == NULL) {
    return 1;
  }
  for (int i = 0; i < newbmp->header.Height; i++) {
    newbmp->table[i] = (RGB*) malloc(newbmp->header.Width * sizeof(RGB));
    if (newbmp->table[i] == NULL) {
      return 1;
    }
    memcpy(newbmp->table[i], bmp->table[i + y] + x, newbmp->header.Width * sizeof(RGB));
  }
  return 0;
}


int rotate(myBmp* bmp, myBmp* newbmp) {
  newbmp->header = bmp->header;
  newbmp->header.Height = bmp->header.Width;
  newbmp->header.Width = bmp->header.Height;
  newbmp->table = (RGB**)malloc(newbmp->header.Height * sizeof(RGB*));
  if (newbmp->table == NULL) {
    return 1;
  }
  for (int i = 0; i < newbmp->header.Height; i++) {
    newbmp->table[i] = (RGB*) malloc(newbmp->header.Width * sizeof(RGB));
    if (newbmp->table[i] == NULL) {
      return 1;
    }
    for (int j = 0; j < newbmp->header.Width; j++) {
      newbmp->table[i][j] = bmp->table[j][newbmp->header.Height - 1 - i];
    }
  }
  return 0;
}

void save_bmp(myBmp* bmp, void *file) {
  bmp->header.ImSize = bmp->header.Height * ((bmp->header.Width * bmp->header.BitCount / 8 + 3) / 4) * 4;
  bmp->header.Size = bmp->header.OffBits + bmp->header.ImSize;
  fwrite(&bmp->header, sizeof(BITMAPINFOHEADER), 1, file);
  int padding = (4 - bmp->header.Width * 3 % 4) % 4;
  char *str = (char*) calloc(padding, sizeof(char));
  for (int i = 0; i < bmp->header.Height; i++) {
    fwrite(bmp->table[i], sizeof(RGB), bmp->header.Width, file);
    fwrite(str, sizeof(char), padding, file);
  }
  free(str);
}


