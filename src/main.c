#include "include.h"

typedef struct {
  char c;
  int size;
  unsigned int rows[];
} Bitmap;

typedef struct {
  int cap_height;
  int x_height;
  int pixel_size;
  int quad_width;
  int font_descent;
  int font_ascent;
  int char_count;
  Bitmap **bitmaps;
} Font;

typedef enum {
  CAP_HEIGHT,
  X_HEIGTH,
  PIXEL_SIZE,
  QUAD_WIDTH,
  FONT_DESCENT,
  FONT_ASCENT,
  ENCODING,
  BITMAP,
  ENDCHAR,
  ENDFONT,
  CHARS,
  SKIP
} Token;

const char *tokens_strings[] = {[CAP_HEIGHT] = "CAP_HEIGHT",
                                [X_HEIGTH] = "X_HEIGHT",
                                [PIXEL_SIZE] = "PIXEL_SIZE",
                                [QUAD_WIDTH] = "QUAD_WIDTH",
                                [FONT_DESCENT] = "FONTT_DESCENT",
                                [FONT_ASCENT] = "FONT_ASCENT",
                                [ENCODING] = "ENCODING",
                                [BITMAP] = "BITMAP",
                                [ENDCHAR] = "ENDCHAR",
                                [CHARS] = "CHARS",
                                [ENDFONT] = "ENDFONT"};

Token find_token(char *line) {
  const int tokens_strings_size =
      sizeof(tokens_strings) / sizeof(tokens_strings[0]);

  for (int i = 0; i < tokens_strings_size; i++) {
    if (strcmp(line, tokens_strings[i]) == 0) {
      return i;
    }
  }

  return SKIP;
}

int init_bdf_from_file(FILE *file, Font *font) {

  char buf[256];
  int count = 0;

  // current bitmap being read
  char curr_char = 0;
  int reading_bitmap = 0;
  Bitmap *curr_bitmap;
  int curr_bitmap_row = 0;

  int curr_bitmap_index = 0;

  while ((fgets(buf, sizeof(buf), file) != NULL) && count < 50) {

    char bufcpy[256];
    strcpy(bufcpy, buf);

    buf[strcspn(buf, "\n")] = '\0';
    buf[strcspn(buf, " ")] = '\0';

    Token token = find_token(buf);

    if (reading_bitmap && token != ENDCHAR) {
      // Read the hex!
      sscanf(buf, "%x", &curr_bitmap->rows[curr_bitmap_row]);
      curr_bitmap_row++;

      printf("---\n Reading HEX: %s \n Current CHAR: %c \n", buf, curr_char);
    }

    switch (token) {
      // grab variables in header
    case SKIP:
      continue;
      break;
    case CAP_HEIGHT:
      sscanf(bufcpy, "%*s %d", &font->cap_height);
      break;
    case X_HEIGTH:
      sscanf(bufcpy, "%*s %d", &font->x_height);
      break;
    case PIXEL_SIZE:
      sscanf(bufcpy, "%*s %d", &font->pixel_size);
      break;
    case QUAD_WIDTH:
      sscanf(bufcpy, "%*s %d", &font->quad_width);
      break;
    case FONT_DESCENT:
      sscanf(bufcpy, "%*s %d", &font->font_descent);
      break;
    case FONT_ASCENT:
      sscanf(bufcpy, "%*s %d", &font->font_ascent);
      break;
    case CHARS:
      // chars is the count of characters in this file
      sscanf(bufcpy, "%*s %d", &font->char_count);
      font->bitmaps = malloc(sizeof(Bitmap *) * font->char_count);
      break;
    case ENCODING:
      // the current character of the bitmap
      int char_code;
      sscanf(bufcpy, "%*s %d", &char_code);
      curr_char = (char)char_code;
      break;
    case BITMAP:
      // start reading hex
      reading_bitmap = 1;

      // make current bitmap
      curr_bitmap =
          malloc(sizeof(Bitmap) + font->pixel_size * sizeof(unsigned int));
      curr_bitmap->c = curr_char;
      curr_bitmap->size = font->pixel_size;
      break;
    case ENDCHAR:
      // stop reading hex
      reading_bitmap = 0;
      curr_bitmap_row = 0;

      // store bitmap
      font->bitmaps[curr_bitmap_index] = curr_bitmap;
      curr_bitmap_index++;
      break;
    case ENDFONT:
      break;
    }
  }

  return 0;
}

int main() {
  FILE *file = fopen("./src/bdf/Tamzen8x15r.bdf", "r");
  if (!file) {
    perror("fopen");
    return 1;
  }

  Font font = {0};

  init_bdf_from_file(file, &font);
  fclose(file);

  return 0;
}
