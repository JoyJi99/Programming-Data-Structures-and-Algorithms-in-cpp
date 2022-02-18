#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned, unsigned);

void run_check(unsigned x, unsigned y, unsigned expected_ans){
  if (power(x,y) != expected_ans){
    printf("%u to %u power error", x, y);
    exit(EXIT_FAILURE);
  }
}

int main(){
  run_check(0, 0, 1);
  run_check(1, 5, 1);
  run_check(0, 1, 0);
  run_check(1, 0, 1);
  run_check(2, 0, 1);
  run_check(3, 4, 81);
  run_check(2141873623,1,2141873623);
  return EXIT_SUCCESS;
}
