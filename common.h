#ifndef COMMON_H
#define COMMON_H
#include <stdio.h>
#ifdef DEBUG_PRINTF // debug -> fprintf into stderr
#define debug(x, ...) do{ fprintf(stderr, x, ##__VA_ARGS__); fflush(stderr); } while(0)
#else // do nothing
#define debug(x, ...) 
#endif
#endif /* COMMON_H */