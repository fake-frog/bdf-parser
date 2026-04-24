#include "include.h"

int main() {
  
  FILE *file = fopen("./src/bdf/Tamzen8x15r.bdf", "r");
  if (!file) {
    perror("fopen");
    return 1;
  }

  Font font = {0};
  init_bdf_from_file(file, &font);
  fclose(file);

  free_font(&font);

  return 0;
}
