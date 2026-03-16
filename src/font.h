#ifndef FONT_H
#define FONT_H

#include <stdio.h>
#include <stdlib.h>

typedef union {
  char *name;
  int val;
} HeaderField;

typedef struct {
  HeaderField *header_fields;
  char c;
  int bitmap_size;
  int pixel_size;
  unsigned int rows[];
} Bitmap;

typedef struct {
  int header_fields_size;
  HeaderField *header_fields;
  int bitmaps_size;
  Bitmap **bitmaps;
  int pixel_size;
} Font;

int init_bdf_from_file(FILE *file, Font *font);
void free_font(Font *font);

#endif
