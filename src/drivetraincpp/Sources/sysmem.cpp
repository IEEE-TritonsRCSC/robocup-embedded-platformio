#include <sys/types.h>

extern "C" void *_sbrk(ptrdiff_t) {
  return (void *)-1;
}

