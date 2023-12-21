#include <sys/unistd.h>

extern int __io_putchar(int ch) __attribute__((weak));
extern int __io_getchar(void) __attribute__((weak));

char *__env[1] = { 0 };
char **environ = __env;

void _exit (int status)
{
  while (1) {}
}

int _open(char *path, int flags, ...)
{
  (void)path;
  (void)flags;
  return -1;
}

int _close(int file)
{
  (void)file;
  return -1;
}

int _lseek(int file, int ptr, int dir)
{
  (void)file;
  (void)ptr;
  (void)dir;
  return 0;
}

__attribute__((weak)) int _read(int file, char *ptr, int len)
{
  (void)file;
  for (int i = 0; i < len; i++)
  {
    *ptr++ = __io_getchar();
  }
  return len;
}

__attribute__((weak)) int _write(int file, char *ptr, int len)
{
  (void)file;
  for (int i = 0; i < len; i++)
  {
    __io_putchar(*ptr++);
  }
  return len;
}

static uint8_t *__sbrk_heap_end = NULL;
extern uint8_t s_heap, e_heap;

void *_sbrk(ptrdiff_t incr)
{
  uint8_t *prev_heap_end;

  // Initialize heap end at first call
  if (NULL == __sbrk_heap_end)
  {
    __sbrk_heap_end = &s_heap;
  }

  // Protect heap from growing into the reserved MSP stack
  if (__sbrk_heap_end + incr > &e_heap)
  {
    return (void *)-1;
  }

  prev_heap_end = __sbrk_heap_end;
  __sbrk_heap_end += incr;

  return (void *)prev_heap_end;
}

