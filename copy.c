#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int a[2048][2048],b[2048][2048];

const unsigned long billion = 1000000000ULL;

unsigned long time_get() {
	struct timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	return billion * t.tv_sec + t.tv_nsec;
}

void copy(int src[2048][2048], int dst[2048][2048]){
  
  for(int i = 0; i < 2048;i++){
    for(int j = 0; j < 2048; j++){
      dst[i][j] = src[i][j];
    }
  }
  
}
void copy2(int src[2048][2048], int dst[2048][2048]){

  for(int i = 0; i < 2048;i++){
    for(int j = 0; j < 2048; j++){
      dst[j][i] = src[j][i];
    }
  }
  
}

int main() {
    unsigned long before, delta;

    
    
    before = time_get();
    copy(a, b);
    delta = time_get() - before;

    printf("copy time: %ld ns\n",delta);

    before = time_get();
    copy2(a, b);
    delta = time_get() - before;

    printf("copy2 time: %ld ns\n",delta);
    
}
  
