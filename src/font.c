#include "include.h"

static int read_header(FILE *file, Font *font) {
  
  const int HEADER_FIELDS_SIZE = 128;
  HeaderField *header_fields = malloc(sizeof(HeaderField) * HEADER_FIELDS_SIZE); 

  int count = 0;
  char line[256];

  while (fgets(line, sizeof(line), file) != NULL || count <= HEADER_FIELDS_SIZE) {

    HeaderField field = {0};
    sscanf(line, "%s %d", field.name, &field.val);
    header_fields[count] = field;

    if (find_token(line) == CHARS) {
      sscanf(line, "%*s %d", &font->bitmaps_size);
      break;
    }

    count++;
  }

  font->header_fields = header_fields;

  return 0;
}

static int read_bitmap(FILE *file, Bitmap *bitmap, int pixel_size) {

  const int HEADER_FIELDS_SIZE = 16;
  HeaderField *header_fields =
      malloc(sizeof(HeaderField) * HEADER_FIELDS_SIZE); // todo free

  int count = 0;
  char line[256];
  char curr_char = 0;
  int encoding = 0;

  while (fgets(line, sizeof(line), file) != NULL ||
         count <= HEADER_FIELDS_SIZE) {

    if (find_token(line) == BITMAP) break;

    if (find_token(line) == ENCODING) {
      sscanf(line, "%*s %d", &encoding);
      curr_char = (char)encoding;
    };

    HeaderField field = {0};
    sscanf(line, "%s %d", field.name, &field.val);
    header_fields[count] = field;
  }

  
  bitmap->c = curr_char;
  count = 0;

  while (fgets(line, sizeof(line), file) != NULL) {

    if (find_token(line) == ENDCHAR || count <= pixel_size) break;
    
    sscanf(line, "%x", &bitmap->rows[count]);
    count++;
  }
  
  return 0;
}

int init_bdf_from_file(FILE *file, Font *font) {
  
  int header_warning = read_header(file, font);
  char line[256];
  fgets(line, sizeof(line), file);

  font->bitmaps = malloc(sizeof(Bitmap *) * font->bitmaps_size);

  for (int i = 0; i < font->bitmaps_size; i++) {
    Bitmap *bitmap = malloc(sizeof(Bitmap) + font->pixel_size * sizeof(unsigned int));
    int bitmap_warning = read_bitmap(file, bitmap, font->pixel_size);
    font->bitmaps[i] = bitmap;
  }
  
  return 1;
}

void free_font(Font *font) {
  
  for (int i = 0; i < font->bitmaps_size; i++) {
    free(font->bitmaps[i]->header_fields);
    free(font->bitmaps[i]);
  }
  free(font->bitmaps);
  free(font->header_fields);
}
