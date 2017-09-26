#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char** argv) {
  const char *input1, *input2, *output;
  FILE *f1 = 0, *f2 = 0, *f3 = 0;

  long size = 0;

  unsigned char *data = 0;

  do {

    if (argc < 4) {
      puts("Usage imgdiff image1 image2 output");
      break;
    }
    input1 = argv[1];
    input2 = argv[2];
    output = argv[3];

    if (!(f1 = fopen(input1, "rb"))) {
      printf("Unable to open input file \'%s\'\n", input1);
      break;
    }

    if (!(f2 = fopen(input2, "rb"))) {
      printf("Unable to open input file \'%s\'\n", input2);
      break;
    }

    if (!(f3 = fopen(output, "wb"))) {
      printf("Unable to open output file \'%s\'\n", output);
      break;
    }

    fseek(f1, 0L, SEEK_END);
    size = ftell(f1);

    fseek(f2, 0L, SEEK_END);
    if (size != ftell(f2)) {
      printf("Input files are different sizes\n");
      break;
    }

    if (!(data = (unsigned char*)malloc(size*2))) {
      printf("Unable to allocate memory\n");
      break;
    }

  } while (0);
  if (data) {
    free(data);
  }
  if (f3) {
    fclose(f3);
  }
  if (f2) {
    fclose(f2);
  }
  if (f1) {
    fclose(f1);
  }
  return 0;
}
