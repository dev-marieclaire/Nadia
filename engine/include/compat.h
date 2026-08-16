#pragma once

#ifdef __DJGPP__

#define AL_INLINE(type, name, args, code) type name args;
#include <allegro.h>
#undef AL_INLINE

#endif
