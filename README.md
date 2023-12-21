# Airos

## Newlib
```c
int _system(const char*);
int _rename(const char*, const char*);
int _isatty(int);
clock_t _times(struct tms*);
int _gettimeofday(struct timeval*, void*);
int _unlink(const char*);
int _link(void);
int _stat(const char*, struct stat*);
int _fstat(int, struct stat*);
int _swistat(int fd, struct stat*);
caddr_t _sbrk(int);
int _getpid(int);
int _close(int);
clock_t _clock(void);
int _swiclose(int);
int _open(const char*, int, ...);
int _swiopen(const char*, int);
int _write(int, char*, int);
int _swiwrite(int, char*, int);
int _lseek(int, int, int);
int _swileek(int, int, int);
int _read(int, char*, int);
int _swiread(int, char*, int);
void initialise_monitor_handles(void);
```

