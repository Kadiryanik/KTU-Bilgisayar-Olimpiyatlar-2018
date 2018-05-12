#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define INPUT_FILE "Soru-3-input.txt"
#define OUTPUT_FILE "Soru-3-output.txt"

// C++ file used for struct constructers

#define TANK_POINT_X 0
#define TANK_POINT_Y 0
#define ENEMY_POINT_X 80
#define ENEMY_POINT_Y 60

/*---------------------------------------------------------------------------*/
typedef struct function{
  // ax + by + c
  float a;
  float b;
  float c;
  function(float i = 0, float j = 0, float k = 0){
    a = i;
    b = j;
    c = k;
  }
} function_t;

/*---------------------------------------------------------------------------*/
typedef struct point{
  float x;
  float y;
  point(float a = 0, float b = 0){
    x = a;
    y = b;
  }
} point_t;

/*---------------------------------------------------------------------------*/
point_t get_point(function_t f1, function_t f2);
function_t get_function(point_t p1, point_t p2);
float get_distance(point_t p1, point_t p2);

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

  int *coordinates = (int *)malloc(size * sizeof(int));
  int offset = 0, counter = 0;
  while (offset < size){
    if(sscanf(buffer + offset, "%d %d %d %d", &coordinates[i++], \
        &coordinates[i++], &coordinates[i++], &coordinates[i++]) == 4){
      counter++;
    }
    while (buffer[offset++] != '\n' && offset < size);
  }

  function_t CD(-4.0 / 3.0, -1, 0);
  point_t enemy(ENEMY_POINT_X, ENEMY_POINT_Y);
  point_t tank(TANK_POINT_X, TANK_POINT_Y);


  file = fopen(OUTPUT_FILE, "w+");
  for (i = 0; i < counter * 4; i += 4){
    point_t p1(coordinates[i + 3], coordinates[i + 2]);
    point_t p2(coordinates[i + 1], coordinates[i]);

    function_t BC = get_function(enemy, p2);
    point_t p4 = get_point(BC, CD);
    
    function_t BD = get_function(enemy, p1);
    point_t p5 = get_point(BD, CD);

    point_t p3((p2.x + p4.x) / 2.0, (p2.y + p4.y) / 2.0);
    point_t p6((p1.x + p5.x) / 2.0, (p1.y + p5.y) / 2.0);

    // can be point_t array but this way suppose much more performance
    float min = get_distance(tank, p1);
    float temp = get_distance(tank, p2);
    char index = '1';
    if (temp < min) {
      min = temp;
      index = '2';
    }
    temp = get_distance(tank, p3);
    if (temp < min) {
      min = temp;
      index = '3';
    }
    temp = get_distance(tank, p4);
    if (temp < min) {
      min = temp;
      index = '4';
    }
    temp = get_distance(tank, p5);
    if (temp < min) {
      min = temp;
      index = '5';
    }
    temp = get_distance(tank, p6);
    if (temp < min) {
      min = temp;
      index = '6';
    }
    fprintf(file, "%c : %4.2f\n", index, min);
  }

  fclose(file);
  return 0;
}

/*---------------------------------------------------------------------------*/
point_t get_point(function_t f1, function_t f2){
  float mult_value = -1.0 / f1.b;
  f1.b *= mult_value;

  f1.a *= mult_value;
  f1.c *= mult_value;

  mult_value = -1.0 / f2.b;
  f2.b *= mult_value;

  f2.a *= mult_value;
  f2.c *= mult_value;

  float a = f1.a - f2.a;
  float c = f2.c - f1.c;

  point_t result;
  if (a == 0){
    printf("get_point 0!\n");
    return result;
  }
  mult_value = 1.0 / a;
  c *= mult_value;

  result.x = c;
  result.y = (f1.a * c + f1.c);

  return result;
}

/*---------------------------------------------------------------------------*/
function_t get_function(point_t p1, point_t p2){
  function_t result;

  if (p2.x - p1.x == 0){
    result.a = 1;
    result.b = 0;
    result.c = p1.x;
  } else{
    result.a = (p2.y - p1.y) / (p2.x - p1.x);
    result.b = -1;
    result.c = p1.y - (result.a * p1.x);
  }

  return result;
}

/*---------------------------------------------------------------------------*/
float get_distance(point_t p1, point_t p2){
  float x = p1.x - p2.x;
  float y = p1.y - p2.y;

  return sqrt(x * x + y * y);
}

/*---------------------------------------------------------------------------*/