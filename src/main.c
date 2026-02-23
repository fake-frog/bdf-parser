#include "include.h"

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
  assert(strlen(hexstring) == 2);

  char hex1 = hexstring[0];
  char hex2 = hexstring[1];

  uint8_t convertedHex1 = convertHexChar(hex1) * 16;
  uint8_t convertedHex2 = convertHexChar(hex2);

  return convertedHex1 + convertedHex2;
}

int readfile(FILE *file) {
  char buf[256];
  int count = 0;
  while ((fgets(buf, sizeof(buf), file) != NULL) && count < 50) {
    printf("%d: %s", count, buf);
    count++;
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
