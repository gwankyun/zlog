#pragma once

#include <Windows.h>
#ifndef Min
#  define Min(a, b) ((a) < (b) ? (a) : (b))
#endif
#include "zlog/module.h"

#ifndef USE_CLASSIC_CONSOLE_API
#  if defined(_WIN32)
#    define USE_CLASSIC_CONSOLE_API 1
#  else
#    define USE_CLASSIC_CONSOLE_API 0
#  endif
#endif
