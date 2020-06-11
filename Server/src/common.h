#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SAFE_DEL(x) if (x) { delete x; x = NULL; }
#define SAFE_DEL_ARRAY(x) if (x) { delete [] x; x = NULL; }
#define MAX(_x, _y) (  (_x) > (_y) ? (_x) : (_y)  );
#define STRINGIFY(x) #x

typedef signed char s8;
typedef unsigned char u8;

typedef signed short s16;
typedef unsigned short u16;

typedef signed int s32;
typedef unsigned int u32;

#define STRLEN(s) (int)strlen(s)

int castPtr(const void* p);
