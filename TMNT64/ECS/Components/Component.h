// At the top
//#define COMPONENT_DEBUG 0

#if COMPONENT_DEBUG
#include <stdio.h>
#define DEBUG_PRINT(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINT(...)
#endif