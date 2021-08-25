#pragma once

#if defined(_WIN32)
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif
#  include <Windows.h>
#endif
#include "zlog/module.h"

#ifndef CXX_VER
#  if __cplusplus >= 201703L
#    define CXX_VER 2017
#  elif __cplusplus >= 201103L
#    define CXX_VER 2011
#  else
#    define CXX_VER 1998
#  endif
#endif

#ifndef HAS_OPTIONAL
#  if defined(__cpp_lib_optional) || CXX_VER >= 2017
#    define HAS_OPTIONAL 1
#  else
#    define HAS_OPTIONAL 0
#  endif
#endif

#ifndef HAS_SPAN
#  if defined(__cpp_lib_span)
#    define HAS_SPAN 1
#  else
#    define HAS_SPAN 0
#  endif
#endif

#ifndef USE_CLASSIC_CONSOLE_API
#  if defined(_WIN32)
#    define USE_CLASSIC_CONSOLE_API 1
#  else
#    define USE_CLASSIC_CONSOLE_API 0
#  endif
#endif
