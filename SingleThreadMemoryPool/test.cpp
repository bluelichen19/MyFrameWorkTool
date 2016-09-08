#include "BlueSingleThreadMemoryPool.h"

int main(int argc, char* argv[]) {
  Rational* array[1000];
  int i, j;
  int64_t start_time = current_time();
  for (j = 0; j < 500; j++) {
    for (i = 0; i < 500; i++) {
      array[i] = new Rational(i);
    }
    for (i = 0; i < 500; i++) {
      delete array[i];
    }
  }
  int64_t end_time = current_time();
  printf("time used:%d\n", end_time - start_time);
  return 0;
}
