#include "glHook.h"

GlPointers glPointers;

#include "glHook_functions.hpp"

#if defined OS_WIN32
	#include "glHook_win32.hpp"
#else
	#include "glHook_posix.hpp"
#endif
