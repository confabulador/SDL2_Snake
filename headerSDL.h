#include <stdlib.h>

#define FALSE 0
#define TRUE 1

#define MOVIMENTO 20

#define LARGURA 800
#define ALTURA 800

#define KEY event.key.keysym.sym

#define FPS 15
#define FRAME_TARGET_TIME (1000 / FPS)


size_t get_rand(size_t min,size_t max){

  size_t retval = rand() % (max - min + 1) + min;
  return retval;
}
