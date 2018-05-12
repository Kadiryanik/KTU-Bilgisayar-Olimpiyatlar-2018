#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "Soru-4-input.txt"
#define OUTPUT_FILE "Soru-4-output.txt"

/*---------------------------------------------------------------------------*/
void to_ten_base(int base, int power, int value, int *result);
int to_other_base(int base, int value);

/*---------------------------------------------------------------------------*/
int main(int argc, char *argv[]){
  FILE *file = NULL;
  char *buffer = NULL;
  int i = 0, size;

  file = fopen(INPUT_FILE, "r");
  if (file == NULL){
    printf("File open failed\n");
    return -1;
  }

  fseek(file, 0L, SEEK_END);
  size = ftell(file);
  fseek(file, 0L, SEEK_SET);

  buffer = (char *)malloc(size * sizeof(char));
  if (buffer == NULL){
    printf("Buffer alloc failed\n");
    return -1;
  }
  fread(buffer, size, sizeof(char), file);
  fclose(file);

  int value = 0, from = 0, to = 0;
  sscanf(buffer, "%d %d %d", &value, &from, &to);

  int result = 0;
  to_ten_base(from, 0, value, &result);
  result = to_other_base(to, result);

  file = fopen(OUTPUT_FILE, "w+");
  fprintf(file, "%d", result);

  fclose(file);
  return 0;
}

/*---------------------------------------------------------------------------*/
void to_ten_base(int base, int power, int value, int *result){
  if (value != 0){
    *result += (value % 10) * pow(base, power);
    to_ten_base(base, ++power, value / 10, result);
  }
  return;
}

/*---------------------------------------------------------------------------*/
int to_other_base(int base, int value){
  int result = 0;
  if (value != 0){
    result = to_other_base(base, value / base);
    result *= 10;
    result += value % base;
  }
  return result;
}

/*---------------------------------------------------------------------------*/