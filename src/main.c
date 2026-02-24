#include "include.h"

typedef struct {
  char c;
  int size;
  uint8_t rows[];
} Bitmap;

typedef struct {
  int cap_height;
  int x_heigth;
  int pixel_size;
  int quad_width;
  int font_descent;
  int font_ascent;
  int char_count;
  Bitmap **bitmaps;
} Font;

uint8_t convertHexChar(char hexChar) {
  uint8_t convertedInt = 0;

  if (hexChar >= '0' && hexChar <= '9') {
    convertedInt = hexChar - '0';
  }
  if (hexChar >= 'A' && hexChar <= 'F') {
    convertedInt = hexChar - 'A' + 10;
  }
  if (hexChar >= 'a' && hexChar <= 'f') {
    convertedInt = hexChar - 'a' + 10;
  }

  return convertedInt;
}

uint8_t readHex(char *hexstring) {
  // maksure its only a byte
  // assert(strlen(hexstring) == 2);

  char hex1 = hexstring[0];
  char hex2 = hexstring[1];

  uint8_t convertedHex1 = convertHexChar(hex1) * 16;
  uint8_t convertedHex2 = convertHexChar(hex2);

  return convertedHex1 + convertedHex2;
}

typedef enum {
  CAP_HEIGHT,
  X_HEIGTH,
  PIXEL_SIZE,
  QUAD_WIDTH,
  FONT_DESCENT,
  FONT_ASCENT,
  CHAR_COUNT,
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
                                [CHAR_COUNT] = "CHAR_COUNT",
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

int readfile(FILE *file) {

  char buf[256];
  int count = 0;

  while ((fgets(buf, sizeof(buf), file) != NULL) && count < 50) {
    // count++;

    char bufcpy[256];
    strcpy(bufcpy, buf);
    buf[strcspn(buf, "\n")] = '\0';
    buf[strcspn(buf, " ")] = '\0';

    Token token = find_token(buf);
    switch (token) {
    case SKIP:
      printf("SKIPED: %s\n", bufcpy);
      continue;
      break;
    case CAP_HEIGHT:
      printf("found: %s\n", bufcpy);
      break;
    case X_HEIGTH:
      printf("found: %s\n", bufcpy);
      break;
    case PIXEL_SIZE:
      printf("found: %s\n", bufcpy);
      break;
    case QUAD_WIDTH:
      printf("found: %s\n", bufcpy);
      break;
    case FONT_DESCENT:
      printf("found: %s\n", bufcpy);
      break;
    case FONT_ASCENT:
      printf("found: %s\n", bufcpy);
      break;
    case CHAR_COUNT:
      printf("found: %s\n", bufcpy);
      break;
    case ENCODING:
      printf("found: %s\n", bufcpy);
      break;
    case BITMAP:
      printf("found: %s\n", bufcpy);
      break;
    case ENDCHAR:
      printf("found: %s\n", bufcpy);
      break;
    case CHARS:
      printf("found: %s\n", bufcpy);
      break;
    case ENDFONT:
      printf("found: %s\n", bufcpy);
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
  readfile(file);
  fclose(file);
  return 0;
}
