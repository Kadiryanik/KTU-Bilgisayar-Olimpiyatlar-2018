#include <stdio.h>
#include <stdlib.h>

#define INPUT_FILE "Soru-2-input.txt"
#define OUTPUT_FILE "Soru-2-output.txt"

#define FAILED  1
#define SUCCEED 0

/*---------------------------------------------------------------------------*/
int increment(int *bytemap, int size);
int check(int *bytemap, int size);
char* fPar(int value, int *counter);

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

  int value = 0;
  sscanf(buffer, "%d", &value);

  int result = 1;
  char* ptr = fPar(value, &result);
  
  file = fopen(OUTPUT_FILE, "w+");
  fprintf(file, "%d : %s\n", result - 1, ptr);

  fclose(file);
  return 0;
}

/*---------------------------------------------------------------------------*/
int increment(int *bytemap, int size){
  int i;
  int carry = 1;

  int flag = 1;
  for (i = 0; i < size / 2; i++){
    if (bytemap[i] == 0){
      flag = 0;
    }
  }
  if (flag){
    return FAILED;
  }
  for (i = size - 2; i >= 0; i--){
    int sum = bytemap[i] + bytemap[i] + carry;
    carry = 0;
    if (sum > 1){
      bytemap[i] = 0;
      carry = 1;
    } else{
      bytemap[i] = 1;
      break;
    }
  }
  return SUCCEED;
}

/*---------------------------------------------------------------------------*/
int check(int *bytemap, int size){
  int i;
  int counter = 0;
  for (i = 0; i < size; i++){
    if (bytemap[i] == 1){
      counter++;
    } else{
      counter--;
    }
    if (counter < 0){
      return FAILED;
    }
  }
  int ones = 0;
  int zeros = 0;
  for (i = 1; i < size - 1; i++){
    if (bytemap[i] == 1){
      ones++;
    } else{
      zeros++;
    }
  }
  if (ones == zeros){
    return SUCCEED;
  }
  return FAILED;
}

/*---------------------------------------------------------------------------*/
char* fPar(int value, int *counter){
  int offset = 0, i, j;
  char* result = (char *)malloc(1000 * sizeof(char));
  if (value == 0){
    return "\0";
  } else if (value == 1){
    return "()\0";
  }
  int size = value * 2;
  int *bytemap = (int *)malloc(size * sizeof(int));
  for (i = 0; i < size; i++){
    bytemap[i] = 0;
  }
  bytemap[0] = 1;
  bytemap[size - 1] = 0;

  while (1){
    if (increment(bytemap, size)){
      break;
    }
    if (check(bytemap, size)){
      continue;
    }

    (*counter)++;
    for (i = 0; i < size; i++){
      if (bytemap[i]){
        result[offset++] = '(';
      } else{
        result[offset++] = ')';
      }
    }
    result[offset++] = ',';
  }
  result[--offset] = '\0';
  return result;
}

/*---------------------------------------------------------------------------*/