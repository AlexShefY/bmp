#pragma once
#include <stdlib.h>
#include <stdio.h>


#pragma pack(push, 1)
typedef struct {
  int16_t Type;
  int32_t Size; 
  int16_t Reserved1; 
  int16_t Reserved2; 
  int32_t OffBits; 
  
  int32_t headerLength;
  int32_t Width;
  int32_t Height;
  int16_t Planes;
  int16_t BitCount;
  int32_t Compression;
  
  int32_t ImSize;
  int32_t xPerMet;
  int32_t yPerMet;
  int32_t ColorsUsed;
  int32_t ColorsImportant;
  
} BITMAPINFOHEADER;
#pragma pack(pop)

typedef struct {
  int8_t blue;
  int8_t green;
  int8_t red;
} RGB;

typedef struct {
  BITMAPINFOHEADER header;
  RGB **table;
} myBmp;

void clean(myBmp *bmp);
int load_bmp(myBmp *bmp, void* file);
void save_bmp(myBmp *bmp, void* file);
